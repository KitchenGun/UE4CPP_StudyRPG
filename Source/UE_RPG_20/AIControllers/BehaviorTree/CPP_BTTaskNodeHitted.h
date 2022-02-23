#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CPP_BTTaskNodeHitted.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_BTTaskNodeHitted : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCPP_BTTaskNodeHitted();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
