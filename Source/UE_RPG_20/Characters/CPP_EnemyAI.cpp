#include "Characters/CPP_EnemyAI.h"
#include "Global.h"
#include "AIControllers/CPP_BehaviorTreeComponent.h"
#include "Weapon/CPP_WeaponComponent.h"
#include "Component/CPP_StateComponent.h"
#include "Component/CPP_PatrolComponent.h"

ACPP_EnemyAI::ACPP_EnemyAI()
{
	CHelpers::CreateActorComponent<UCPP_BehaviorTreeComponent>(this,&Behavior,"Behavior");
	CHelpers::CreateActorComponent<UCPP_PatrolComponent>(this,&Patrol,"Patrol");
}

void ACPP_EnemyAI::BeginPlay()
{
	Super::BeginPlay();
	CheckFalse(State->IsIdleMode())
	Weapon->SetOneHandMode();
}
