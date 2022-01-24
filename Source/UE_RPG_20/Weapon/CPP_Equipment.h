#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_Equipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipAndUnEquip);

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;
	UPROPERTY(EditAnywhere)
	float PlayRatio = 1;
	UPROPERTY(EditAnywhere)
	bool bCanMove = true;
	UPROPERTY(EditAnywhere)
	bool bLookForward = true;

};

UCLASS(Blueprintable)
class UE_RPG_20_API UCPP_Equipment : public UObject
{
	GENERATED_BODY()
	
public:
	UCPP_Equipment();

	void BeginPlay(class ACharacter* InOwner, const FEquipmentData& InData);
	//UFUNCTION(BlueprintImplementableEvent) : 선언부분은 CPP 에서 하지만 구현부는 BP에서 진행한다
	//UFUNCTION(BlueprintNativeEvent) : 
	
	UFUNCTION(BlueprintNativeEvent)
	void Equip();
	virtual void Equip_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void Begin_Equip();
	virtual void Begin_Equip_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void End_Equip();
	virtual void End_Equip_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void UnEquip();
	virtual void UnEquip_Implementation();

public://대리자 선언
	FEquipAndUnEquip OnEquip();
	FEquipAndUnEquip OnUnEquip();

protected:
	class ACharacter* OwnerCharacter;
	class UCPP_StateComponent* State;
	class UCPP_StatusComponent* Status;

	FEquipmentData Data;
	bool bEquipping;

};
