#include "AIControllers/BehaviorTree/CPP_BTTaskNodePatrol.h"
#include "Global.h"
#include "AIControllers/CPP_AIController.h"
#include "Characters/CPP_EnemyAI.h"
#include "Component/CPP_PatrolComponent.h"

UCPP_BTTaskNodePatrol::UCPP_BTTaskNodePatrol()
{
	bNotifyTick = true;
	NodeName ="Patrol";
}

EBTNodeResult::Type UCPP_BTTaskNodePatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACPP_AIController* controller = Cast<ACPP_AIController>(OwnerComp.GetOwner());
	ACPP_EnemyAI* ai = Cast<ACPP_EnemyAI>(controller->GetPawn());
	UCPP_PatrolComponent* patrol = CHelpers::GetComponent<UCPP_PatrolComponent>(ai);
	FVector location;
	float distance;
	if(patrol->GetMoveTo(location,distance)==false)
	{return EBTNodeResult::Failed;}
	return EBTNodeResult::InProgress;
}

void UCPP_BTTaskNodePatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	ACPP_AIController* controller = Cast<ACPP_AIController>(OwnerComp.GetOwner());
	ACPP_EnemyAI* ai = Cast<ACPP_EnemyAI>(controller->GetPawn());
	UCPP_PatrolComponent* patrol = CHelpers::GetComponent<UCPP_PatrolComponent>(ai);
	
	FVector location;
	float distance;
	
	patrol->GetMoveTo(location,distance);
	
	EPathFollowingRequestResult::Type type = controller->MoveToLocation(location,distance,false);
	if(type == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
		return;
	}
	if(type == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		patrol->UpdateNextIndex();
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
	
}
