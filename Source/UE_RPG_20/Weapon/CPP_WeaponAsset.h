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
	void BeginPlay(class ACharacter* InOwner);
	void EndPlay();

	FORCEINLINE class ACPP_Attachment* GetAttachment() {return Attachment;}
	FORCEINLINE class UCPP_Equipment* GetEquipment() { return Equipment; }
	FORCEINLINE class UCPP_DoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class UCPP_SubAction* GetSubAction() {return SubAction;}
private:
	UPROPERTY()
	class ACPP_Attachment* Attachment;

	UPROPERTY()
	class UCPP_Equipment* Equipment;

	UPROPERTY()
	class UCPP_DoAction* DoAction;

	UPROPERTY()
	class UCPP_SubAction* SubAction;
};
