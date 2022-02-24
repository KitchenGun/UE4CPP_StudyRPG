#include "AIControllers/BehaviorTree/CPP_BTTaskNodeAction.h"
#include "Global.h"
#include "Characters/CPP_EnemyAI.h"
#include "AIControllers/CPP_AIController.h"
#include "Component/CPP_StateComponent.h"
#include "Weapon/CPP_WeaponComponent.h"


UCPP_BTTaskNodeAction::UCPP_BTTaskNodeAction()
{
	bNotifyTick = true;
	NodeName = "Action";
}

EBTNodeResult::Type UCPP_BTTaskNodeAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACPP_AIController* controller = Cast<ACPP_AIController>(OwnerComp.GetOwner());
	ACPP_EnemyAI* ai = Cast<ACPP_EnemyAI>(controller->GetPawn());
	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(ai);

	if(weapon)
		weapon->DoAction();
	
	TotalTime = 0.0f;
	controller->StopMovement();
	
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UCPP_BTTaskNodeAction::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	ACPP_AIController* controller = Cast<ACPP_AIController>(OwnerComp.GetOwner());
	ACPP_EnemyAI* ai = Cast<ACPP_EnemyAI>(controller->GetPawn());
	UCPP_StateComponent* state = CHelpers::GetComponent<UCPP_StateComponent>(ai);

	state->SetIdleMode();
	
	return EBTNodeResult::Succeeded;
}

void UCPP_BTTaskNodeAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	ACPP_AIController* controller = Cast<ACPP_AIController>(OwnerComp.GetOwner());
	ACPP_EnemyAI* ai = Cast<ACPP_EnemyAI>(controller->GetPawn());
	UCPP_StateComponent* state = CHelpers::GetComponent<UCPP_StateComponent>(ai);
	TotalTime+=DeltaSeconds;

	if(state->IsIdleMode()&&TotalTime>Delay)
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	
}
