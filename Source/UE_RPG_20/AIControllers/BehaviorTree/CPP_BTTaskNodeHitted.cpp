#include "AIControllers/BehaviorTree/CPP_BTTaskNodeHitted.h"
#include "Global.h"
#include "AIControllers/CPP_AIController.h"
#include "Characters/CPP_EnemyAI.h"

UCPP_BTTaskNodeHitted::UCPP_BTTaskNodeHitted()
{
	bNotifyTick = true;
	NodeName ="Hitted";
}

EBTNodeResult::Type UCPP_BTTaskNodeHitted::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACPP_AIController* controller = Cast<ACPP_AIController>(OwnerComp.GetOwner());
	ACPP_EnemyAI* ai = Cast<ACPP_EnemyAI>(controller->GetPawn());
	controller->StopMovement();
	return EBTNodeResult::InProgress;
}

void UCPP_BTTaskNodeHitted::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	ACPP_AIController* controller = Cast<ACPP_AIController>(OwnerComp.GetOwner());
	ACPP_EnemyAI* ai = Cast<ACPP_EnemyAI>(controller->GetPawn());
	UCPP_StateComponent* state = CHelpers::GetComponent<UCPP_StateComponent>(ai);
	if(state->IsIdleMode())
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
}
