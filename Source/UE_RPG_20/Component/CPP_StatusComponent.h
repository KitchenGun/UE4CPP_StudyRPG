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
public:	
	UCPP_StatusComponent();

	void AddHealth(float InAmount);
	void SubHealth(float InAmount);
protected:
	virtual void BeginPlay() override;
private:
	bool bCanMove = true;
	float Health;
		
};
