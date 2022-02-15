#include "Weapon/CPP_SubActionMeteor.h"
#include "CPP_SkillThron.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"

UCPP_SubActionMeteor::UCPP_SubActionMeteor() {}

void UCPP_SubActionMeteor::Pressed()
{
	CheckFalse(State->IsIdleMode());
	CheckFalse(State->IsSubActionMode());
	Super::Pressed();
	State->SetActionMode();
	State->OnSubActionMode();
	ActionData.PlayMontage(OwnerCharacter);
}

void UCPP_SubActionMeteor::Begin_SubAction()
{
	Super::Begin_SubAction();
	if(SkillClass)
	{
		FActorSpawnParameters params;
		params.Owner = OwnerCharacter;

		FTransform transform = SkillTransform;
		FVector location = OwnerCharacter->GetActorLocation();
		location+=OwnerCharacter->GetActorRotation().RotateVector(transform.GetLocation());
		transform.SetLocation(location);
		transform.SetRotation(FQuat(OwnerCharacter->GetActorRotation()));
		ACPP_Skill* skill = World->SpawnActorDeferred<ACPP_SkillThron>(SkillClass,transform,OwnerCharacter);
		skill->SetHitData(HitData);
		UGameplayStatics::FinishSpawningActor(skill,transform);
	}
}

void UCPP_SubActionMeteor::End_SubAction()
{
	Super::End_SubAction();
	State->OffSubActionMode();
	ActionData.EndAction(OwnerCharacter);
}
