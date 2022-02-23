#include "AIControllers/BehaviorTree/CPP_BTTaskNodeSpeed.h"
#include "Global.h"
#include "AIControllers/CPP_AIController.h"
#include "Characters/CPP_EnemyAI.h"


UCPP_BTTaskNodeSpeed::UCPP_BTTaskNodeSpeed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCPP_BTTaskNodeSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACPP_AIController* controller = Cast<ACPP_AIController>(OwnerComp.GetOwner());
	ACPP_EnemyAI* ai = Cast<ACPP_EnemyAI>(controller->GetPawn());
	UCPP_StatusComponent* status = CHelpers::GetComponent<UCPP_StatusComponent>(ai);
	status->SetSpeed(Type);
	
	return EBTNodeResult::Succeeded;
}
