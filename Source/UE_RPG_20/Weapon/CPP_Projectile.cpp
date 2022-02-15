#include "Weapon/CPP_Projectile.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"


ACPP_Projectile::ACPP_Projectile()
{
	CHelpers::CreateComponent<USphereComponent>(this,&Sphere,"Sphere");
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this,&Projectile,"Projectile");

	Projectile->ProjectileGravityScale =0.0f;
	
}

void ACPP_Projectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentHit.AddDynamic(this,&ACPP_Projectile::OnComponentHit);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Projectile->Deactivate();
}

void ACPP_Projectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if(OnProjectileEndPlay.IsBound())
		OnProjectileEndPlay.Broadcast(this);
}

void ACPP_Projectile::Shoot(const FVector& InForward)
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true));
	Projectile->Velocity = InForward*Projectile->InitialSpeed;
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Projectile->Activate();
}

void ACPP_Projectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SetLifeSpan(0.5f);
	for(AActor* actor:IgnoreActors)
		CheckTrue(actor == OtherActor);
	ACharacter* character = Cast<ACharacter>(OtherActor);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if(character&&OnProjectileHit.IsBound())
		OnProjectileHit.Broadcast(this,character);
}
