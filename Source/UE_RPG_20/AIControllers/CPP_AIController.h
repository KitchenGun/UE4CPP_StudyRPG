#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "CPP_AIController.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_AIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UAIPerceptionComponent* Perception;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_BehaviorTreeComponent* Behavior;
public:
	ACPP_AIController();
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
private:
	class ACPP_EnemyAI* OwnerCharacter;
	class UAISenseConfig_Sight* SightSense;
};
