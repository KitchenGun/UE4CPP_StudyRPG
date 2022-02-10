#include "Weapon/CPP_SubActionSlach.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"
#include "CPP_SkillSwordSlash.h"

UCPP_SubActionSlach::UCPP_SubActionSlach()
{

}

void UCPP_SubActionSlach::Pressed()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(State->IsSubActionMode());
	Super::Pressed();
	State->SetActionMode();
	State->OnSubActionMode();
	ActionData.PlayMontage(OwnerCharacter);
}

void UCPP_SubActionSlach::Begin_SubAction()
{
	Super::Begin_SubAction();
	if(SkillClass)
	{
		FActorSpawnParameters params;
		params.Owner = OwnerCharacter;
		FTransform transform = SkillTransform;
		transform.AddToTranslation(OwnerCharacter->GetActorLocation());
		transform.SetRotation(FQuat(OwnerCharacter->GetActorRotation()));
		//������ �Ҷ� scale�� �ǵ帱���ֵ��� �ϴ� ���� SpawnActorDeferred
		ACPP_Skill* skill = World->SpawnActorDeferred<ACPP_SkillSwordSlash>(SkillClass,transform,OwnerCharacter);
		skill->SetHitData(HitData);
		//�� ����Ҷ� FinishSpawningActor�� ����ؾ��Ѵ�
		UGameplayStatics::FinishSpawningActor(skill,transform);
	}
	
}

void UCPP_SubActionSlach::End_SubAction()
{
	Super::End_SubAction();
	State->OffSubActionMode();
	ActionData.EndAction(OwnerCharacter);
	
}
