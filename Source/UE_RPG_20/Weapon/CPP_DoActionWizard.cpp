#include "Weapon/CPP_DoActionWizard.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"

UCPP_DoActionWizard::UCPP_DoActionWizard()
{
}

void UCPP_DoActionWizard::BeginPlay(ACPP_Attachment* InAttachment, ACharacter* InOwner,
	const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas)
{
	Super::BeginPlay(InAttachment, InOwner, InActionDatas, InHitDatas);
}

void UCPP_DoActionWizard::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);
}

void UCPP_DoActionWizard::DoAction()
{
	Super::DoAction();
	CheckFalse(ActionDatas.Num()>0);
	CheckFalse(State->IsIdleMode());
	ActionDatas[0].PlayMontage(OwnerCharacter);
}

void UCPP_DoActionWizard::BeginDoAction()
{
	Super::BeginDoAction();
}

void UCPP_DoActionWizard::EndDoAction()
{
	Super::EndDoAction();
	ActionDatas[0].EndAction(OwnerCharacter);
}

void UCPP_DoActionWizard::OnFireballBeginOverlap(AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	HitDatas[0].SendDamage(OwnerCharacter,InAttackCauser,InOtherCharacter);
}

