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

//매개변수 하나를 대리자 동적으로 여러곳에 호출 (이름 ,형식,변수)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCPP_StateComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	//실행을 하지 않아도 독립적으로 실행 가능
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
