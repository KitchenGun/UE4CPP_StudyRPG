#include "AIControllers/CPP_BehaviorTreeComponent.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"


bool UCPP_BehaviorTreeComponent::IsWaitMode()
{
	return GetType() == EBehaviorType::Wait;
}

bool UCPP_BehaviorTreeComponent::IsApproachMode()
{
	return GetType() == EBehaviorType::Approach;
}

bool UCPP_BehaviorTreeComponent::IsActionMode()
{
	return GetType() == EBehaviorType::Action;
}

bool UCPP_BehaviorTreeComponent::IsPatrolMode()
{
	return GetType() == EBehaviorType::Patrol;
}

bool UCPP_BehaviorTreeComponent::IsHittedMode()
{
	return GetType() == EBehaviorType::Hitted;
}

void UCPP_BehaviorTreeComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UCPP_BehaviorTreeComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void UCPP_BehaviorTreeComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UCPP_BehaviorTreeComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UCPP_BehaviorTreeComponent::SetHittedMode()
{
	ChangeType(EBehaviorType::Hitted);
}

ACPlayer* UCPP_BehaviorTreeComponent::GetTargetPlayer()
{
	return Cast<ACPlayer>(BlackBoard->GetValueAsObject(PlayerKey));
}

FVector UCPP_BehaviorTreeComponent::GetLocation()
{
	return BlackBoard->GetValueAsVector(LocationKey);
}

void UCPP_BehaviorTreeComponent::ChangeType(EBehaviorType InType)
{
	BlackBoard->SetValueAsEnum(BehaviorKey,(uint8)InType);
	if(OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(InType);
}

EBehaviorType UCPP_BehaviorTreeComponent::GetType()
{
	return (EBehaviorType)BlackBoard->GetValueAsEnum(BehaviorKey);
}

UCPP_BehaviorTreeComponent::UCPP_BehaviorTreeComponent()
{}


void UCPP_BehaviorTreeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

