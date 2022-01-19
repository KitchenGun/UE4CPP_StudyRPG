#include "CPP_Sword.h"
#include "Global.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Component/CPP_StatusComponent.h"
#include "Component/CPP_StateComponent.h"
#include "Animation/AnimMontage.h"

ACPP_Sword::ACPP_Sword()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	CHelpers::CreateComponent<UCapsuleComponent>(this, &Capsule, "Capsule", Mesh);

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Weapons/Sword/SK_Sword.SK_Sword'");
	Mesh->SetSkeletalMesh(mesh);

	Capsule->SetRelativeLocation(FVector(-13, -130, 0));
	Capsule->SetRelativeRotation(FRotator(0, 0, 90));
	Capsule->SetCapsuleHalfHeight(220);
	Capsule->SetCapsuleRadius(11);

	CHelpers::GetAsset<UAnimMontage>(&EquipMontage, "AnimMontage'/Game/Character/Montages/OneHand/Draw_Sword_Montage.Draw_Sword_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&ComboMontage[0], "AnimMontage'/Game/Character/Montages/OneHand/Sword_Attack_1_Montage.Sword_Attack_1_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&ComboMontage[1], "AnimMontage'/Game/Character/Montages/OneHand/Sword_Attack_2_Montage.Sword_Attack_2_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&ComboMontage[2], "AnimMontage'/Game/Character/Montages/OneHand/Sword_Attack_3_Montage.Sword_Attack_3_Montage'");
}

void ACPP_Sword::Equip()
{
	CheckFalse(State->IsIdleMode());
	if (bEquipped)
	{
		UnEquip();
		return;
	}

	State->SetEquipMode();
	OwnerCharacter->PlayAnimMontage(EquipMontage, 2.0f);
}

void ACPP_Sword::Begin_Equip()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "Hand_OneHand");

	bEquipped = true;
}

void ACPP_Sword::End_Equip()
{
	State->SetIdleMode();
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACPP_Sword::UnEquip()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "Holster_OneHand");
	bEquipped = false;
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}


void ACPP_Sword::OnCollision()
{
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACPP_Sword::OffCollision()
{
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACPP_Sword::Action()
{
	CheckFalse(bEquipped);
	if (bEnable)
	{
		bExist = true;
		bEnable = false;
		return;
	}
	CheckFalse(State->IsIdleMode());

	Status->Stop();
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(ComboMontage[Index],1.5f);
}

void ACPP_Sword::Begin_Action()
{
	CheckFalse(bExist);
	bExist = false;

	OwnerCharacter->PlayAnimMontage(ComboMontage[++Index],1.5f);
}

void ACPP_Sword::End_Action()
{
	Index =0;

	Status->Move();
	State->SetIdleMode();
}

void ACPP_Sword::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCPP_StateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCPP_StatusComponent>(OwnerCharacter);

	OffCollision();
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Sword::OnComponentBeginOverlap);
}

void ACPP_Sword::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
//데미지 구현
	CheckTrue(OtherActor == OwnerCharacter);
	FDamageEvent DE;
	OtherActor->TakeDamage(20,DE,OwnerCharacter->GetController(),this);
}

