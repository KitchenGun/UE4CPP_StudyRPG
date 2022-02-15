#pragma once

#include "CoreMinimal.h"
#include "CPP_WeaponStructures.h"
#include "Weapon/CPP_SubAction.h"
#include "CPP_SubActionMeteor.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_SubActionMeteor : public UCPP_SubAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly,Category="Skill")
	TSubclassOf<class ACPP_SkillThron> SkillClass;
	UPROPERTY(EditDefaultsOnly,Category="Skill")
	FTransform SkillTransform;
	UPROPERTY(EditDefaultsOnly,Category="Data")
	FDoActionData ActionData;
	UPROPERTY(EditDefaultsOnly,Category="Data")
	FHitData HitData;

public:
	UCPP_SubActionMeteor();
	virtual void Pressed() override;
	virtual void Begin_SubAction() override;
	virtual void End_SubAction() override;
	
	
};
