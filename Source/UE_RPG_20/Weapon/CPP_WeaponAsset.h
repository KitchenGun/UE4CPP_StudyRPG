#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CPP_WeaponStructures.h"
#include "CPP_Equipment.h"
#include "CPP_WeaponAsset.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_WeaponAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class ACPP_Attachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UCPP_Equipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FEquipmentData EquipmentData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UCPP_DoAction> DoActionClass;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TArray<FDoActionData> DoActionDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FHitData> HitDatas;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UCPP_SubAction> SubActionClass;
public:
	UCPP_WeaponAsset();
	void BeginPlay(class ACharacter* InOwner,class UCPP_WeaponData** OutAction);
	void EndPlay();

};
