#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CPP_BTTaskNodeAction.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_BTTaskNodeAction : public UBTTaskNode
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere,Category="AI")
	float Delay = 2.0f;
public:
	UCPP_BTTaskNodeAction();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	float TotalTime;
};
