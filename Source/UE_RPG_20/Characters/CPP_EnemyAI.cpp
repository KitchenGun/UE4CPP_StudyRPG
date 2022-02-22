#include "Characters/CPP_EnemyAI.h"
#include "Global.h"
#include "AIControllers/CPP_BehaviorTreeComponent.h"


ACPP_EnemyAI::ACPP_EnemyAI()
{
	CHelpers::CreateActorComponent<UCPP_BehaviorTreeComponent>(this,&Behavior,"Behavior");
}

void ACPP_EnemyAI::BeginPlay()
{
	Super::BeginPlay();
}
