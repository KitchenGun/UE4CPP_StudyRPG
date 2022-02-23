#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Component/CPP_StatusComponent.h"
#include "CPP_BTTaskNodeSpeed.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_BTTaskNodeSpeed : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere,Category="Speed")
	ESpeedType Type;
	public:
	UCPP_BTTaskNodeSpeed();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
