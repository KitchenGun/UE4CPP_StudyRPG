#include "Weapon/CPP_Attachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"

ACPP_Attachment::ACPP_Attachment()
{
	CHelpers::CreateComponent<USceneComponent>(this,&Root,"Root");
}

void ACPP_Attachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	GetComponents<UShapeComponent>(Collisions);
	for (UShapeComponent* collision : Collisions)
	{
		collision->OnComponentBeginOverlap.AddDynamic(this,&ACPP_Attachment::OnComponentBeginOverlap);
		collision->OnComponentEndOverlap.AddDynamic(this,&ACPP_Attachment::OnComponentEndOverlap);
	}
	Super::BeginPlay();
}

void ACPP_Attachment::OnCollision()
{
	for (UShapeComponent* collision : Collisions)
	{
		collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACPP_Attachment::OffCollision()
{
	for (UShapeComponent* collision : Collisions)
	{
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


void ACPP_Attachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative,true),InSocketName);
}

void ACPP_Attachment::AttachCollision(FName InSocketName)
{
	for (UShapeComponent* collision : Collisions)
	{
		if(collision->GetName()==InSocketName.ToString())
		{
			AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
			return;
		}
	}
}

void ACPP_Attachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass()==OtherActor->GetClass());//객체에 맞는 자료형인지 비교

	//바인딩으로 호출
	if(OnAttachmentBeginOverlap.IsBound())
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter,this,Cast<ACharacter>(OtherActor));

}

void ACPP_Attachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());//객체에 맞는 자료형인지 비교

	//바인딩으로 호출
	if (OnAttachmentEndOverlap.IsBound())
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));

}
