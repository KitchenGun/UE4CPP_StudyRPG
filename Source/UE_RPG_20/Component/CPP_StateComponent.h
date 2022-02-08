#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_StateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType :uint8
{
	Idle,
	Equip,
	Hitted,
	Dead,
	Action,
	MAX
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateTypeChanged, EStateType, InNewType);

//�Ű����� �ϳ��� �븮�� �������� �������� ȣ�� (�̸� ,����,����)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCPP_StateComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	//������ ���� �ʾƵ� ���������� ���� ����
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsIdleMode() {return Type == EStateType::Idle;}
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsSubActionMode() { return bInSubAction; }

public:	
	UCPP_StateComponent();

	void SetIdleMode();
	void SetEquipMode();
	void SetHittedMode();
	void SetDeadMode();
	void SetActionMode();

	void OnSubActionMode();
	void OffSubActionMode();
protected:
	virtual void BeginPlay() override;

private:
	void ChangeType(EStateType InType);
public:
	FStateTypeChanged OnStateTypeChanged;
private:
	EStateType Type;
	bool bInSubAction = false;
};
