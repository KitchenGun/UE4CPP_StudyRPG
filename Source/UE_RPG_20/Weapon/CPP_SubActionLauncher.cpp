#include "Weapon/CPP_SubActionLauncher.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

UCPP_SubActionLauncher::UCPP_SubActionLauncher(){}

void UCPP_SubActionLauncher::BeginPlay(ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);
	OwnerRadius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
}

void UCPP_SubActionLauncher::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);
}

void UCPP_SubActionLauncher::Pressed()
{
	Super::Pressed();
}

void UCPP_SubActionLauncher::Begin_SubAction()
{
	Super::Begin_SubAction();
	bMoving = true;
	Start = OwnerCharacter->GetActorLocation();
	End = Start+OwnerCharacter->GetActorForwardVector()*Distance;

	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);
	TArray<FHitResult> hitResults;

	float y = OwnerRadius;
	float z = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FRotator rotation = OwnerCharacter->GetActorRotation();

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery3);
	UKismetSystemLibrary::BoxTraceMultiForObjects(OwnerCharacter->GetWorld(),Start,End,FVector(0,y,z),
		rotation,objects,false,ignores,DrawDebug,hitResults,true);

	for (const FHitResult& hitResult : hitResults)
	{
		ACharacter* character = Cast<ACharacter>(hitResult.GetActor());
		if(character)
		{
			character->GetCapsuleComponent()->SetCollisionProfileName("Launcher");
			Overlapped.AddUnique(character);
		}
	}
}

void UCPP_SubActionLauncher::End_SubAction()
{
	Super::End_SubAction();
	bMoving = false;
	for (ACharacter* character : Overlapped)
	{
		character->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
	}
	ActionData.EndAction(OwnerCharacter);
}


void UCPP_SubActionLauncher::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);

	for (ACharacter* character : Hitted)
	{
		CheckTrue(character == InOtherCharacter);
	}

	Hitted.AddUnique(InOtherCharacter);

	HitData.SendDamage(OwnerCharacter,InAttackCauser,InOtherCharacter);
}

