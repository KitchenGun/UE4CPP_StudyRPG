#include "AIControllers/BehaviorTree/CPP_BTService_Melee.h"
#include "Global.h"
#include "Characters/CPP_EnemyAI.h"
#include "Characters/CPlayer.h"
#include "AIControllers/CPP_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Component/CPP_StateComponent.h"
#include "Component/CPP_PatrolComponent.h"
#include "AIControllers/CPP_BehaviorTreeComponent.h"

UCPP_BTService_Melee::UCPP_BTService_Melee()
{
	NodeName="Melee";
}

void UCPP_BTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	ACPP_AIController* controller = Cast<ACPP_AIController>(OwnerComp.GetOwner());
	ACPP_EnemyAI* ai = Cast<ACPP_EnemyAI>(controller->GetPawn());
	UCPP_StateComponent* state = CHelpers::GetComponent<UCPP_StateComponent>(ai);
	UCPP_BehaviorTreeComponent* behavior = CHelpers::GetComponent<UCPP_BehaviorTreeComponent>(ai);

	if(state->IsHittedMode())
	{
		behavior->SetHittedMode();
		return;
	}
	ACPlayer* player = behavior->GetTargetPlayer();
	if(!player)
	{
		UCPP_PatrolComponent* patrol = CHelpers::GetComponent<UCPP_PatrolComponent>(ai);

		if(patrol)
		{
			behavior->SetPatrolMode();
			return;
		}
		
		
		behavior->SetWaitMode();
		return;
	}
	float distance = ai->GetDistanceTo(player);
	if(distance<ActionRange)
	{
		behavior->SetActionMode();
		return;
	}
	behavior->SetApproachMode();
	
	
}
