
#include "CPP_DoActionCombo.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"

void UCPP_DoActionCombo::DoAction()
{
	Super::DoAction();
	CheckFalse(ActionDatas.Num()>0);

	if (bEnable == true)
	{
		bExist = true;
		bEnable = false;
		
		return;
	}
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	
	ActionDatas[Index].PlayMontage(OwnerCharacter);
}

void UCPP_DoActionCombo::BeginDoAction()
{
	Super::BeginDoAction();
	CheckFalse(bExist);
	bExist = false;

	Index++;
	ActionDatas[Index].PlayMontage(OwnerCharacter);
}

void UCPP_DoActionCombo::EndDoAction()
{
	Super::EndDoAction();
	ActionDatas[Index].EndAction(OwnerCharacter);
	Index =0;
}

void UCPP_DoActionCombo::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser,InOtherCharacter);
	CheckFalse(State->IsActionMode());
	CheckNull(InOtherCharacter);
	for (ACharacter* hitted : Hitted)
	{
		CheckTrue(hitted == InOtherCharacter);
	}

	Hitted.AddUnique(InOtherCharacter);

	HitDatas[Index].SendDamage(InAttacker,InAttackCauser,InOtherCharacter);
}

void UCPP_DoActionCombo::OffAttachmentCollision()
{
	Super::OffAttachmentCollision();
	CheckFalse(State->IsActionMode());
	Hitted.Empty();
}
