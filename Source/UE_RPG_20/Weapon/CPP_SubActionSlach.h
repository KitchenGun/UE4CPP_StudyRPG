#pragma once

#include "CoreMinimal.h"
#include "Weapon/CPP_SubAction.h"
#include "Weapon/CPP_WeaponStructures.h"
#include "CPP_SubActionSlach.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_SubActionSlach : public UCPP_SubAction
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly,Category="Skill")
	TSubclassOf<class ACPP_SkillSwordSlash> SkillClass;
	UPROPERTY(EditDefaultsOnly,Category="Skill")
	FTransform SkillTransform;
	UPROPERTY(EditDefaultsOnly,Category="Skill")
	FDoActionData ActionData;
	UPROPERTY(EditDefaultsOnly,Category="Skill")
	FHitData HitData;
public:
	UCPP_SubActionSlach();
	virtual void Pressed() override;
	virtual void Begin_SubAction() override;
	virtual void End_SubAction() override;
};
