#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_StatusComponent.generated.h"

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Walk,
	Run,
	Sprint,
	Max
};

UENUM()
enum EStatusType
{
	Bag,
	Battery,
	Book,
	Bomb,
	Gun,
	HP,
	Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeStatus,float, value);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCPP_StatusComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed[(int32)ESpeedType::Max] = {200,400,600};

	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxHealth = 600;

public:
	FORCEINLINE float GetWalkSpeed() const { return Speed[(int32)ESpeedType::Walk]; }
	FORCEINLINE float GetRunSpeed() const { return Speed[(int32)ESpeedType::Run]; }
	FORCEINLINE float GetSprintSpeed() const { return Speed[(int32)ESpeedType::Sprint]; }

	FORCEINLINE bool CanMove() const { return bCanMove; }

	FORCEINLINE float GetMaxHp() const { return MaxHealth; }
	FORCEINLINE float GetHP() const { return Health; }

	FORCEINLINE void Move()  { bCanMove = true; }
	FORCEINLINE void Stop()  { bCanMove = false; }

	FORCEINLINE bool GetFixedCamera() const {return bFixedCamera; }
	FORCEINLINE void EnableFixedCamera() {bFixedCamera=true;}
	FORCEINLINE void DisableFixedCamera() {bFixedCamera=false;}
public:	
	UCPP_StatusComponent();

	void AddHealth(float InAmount);
	UFUNCTION()
	void AddMaxHealth();
	UFUNCTION()
	void SubMaxHealth();

	void SubHealth(float InAmount);

	void SetSpeed(ESpeedType InType);
	
protected:
	virtual void BeginPlay() override;
private:
	class ACharacter* OwnerCharacter;
	
	bool bCanMove = true;
	float Health;
	bool bFixedCamera;

public:
	FOnChangeStatus OnChangeHPEvent;
};
