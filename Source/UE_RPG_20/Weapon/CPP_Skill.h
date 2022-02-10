#pragma once
#include "CoreMinimal.h"
#include "CPP_WeaponStructures.h"
#include "GameFramework/Actor.h"
#include "CPP_Skill.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_Skill : public AActor
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetHitData(FHitData InHitData) { HitData = InHitData; }
	
public:	
	ACPP_Skill();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;
protected:
	class ACharacter* OwnerCharacter;
	FDoActionData ActionData;
	FHitData HitData;
};
