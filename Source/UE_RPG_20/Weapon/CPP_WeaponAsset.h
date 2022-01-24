#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CPP_WeaponStructures.h"
#include "CPP_WeaponAsset.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_WeaponAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UCPP_Equipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TArray<FDoActionData> DoActionDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FHitData> HitDatas;
};
