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

void UCPP_StateComponent::OnSubActionMode()
{
	bInSubAction = true;
}

void UCPP_StateComponent::OffSubActionMode()
{
	bInSubAction = false;
}

void  UCPP_StateComponent::ChangeType(EStateType InType)
{
	Type = InType;
	
	if(OnStateTypeChanged.IsBound())//바인딩이 되어있다면 호출한다
		OnStateTypeChanged.Broadcast(InType);//대리자 호출
}
