#include "Component/CPP_StateComponent.h"

UCPP_StateComponent::UCPP_StateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCPP_StateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void  UCPP_StateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void  UCPP_StateComponent::SetEquipMode()
{
	ChangeType(EStateType::Equip);
}

void UCPP_StateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

void UCPP_StateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

void UCPP_StateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void  UCPP_StateComponent::ChangeType(EStateType InType)
{
	Type = InType;
}
