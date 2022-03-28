
#include "Component/CPP_StatusComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCPP_StatusComponent::UCPP_StatusComponent()
{
}

void UCPP_StatusComponent::AddHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	if(OnChangeHPEvent.IsBound())
		OnChangeHPEvent.Broadcast(Health/MaxHealth);
}

void UCPP_StatusComponent::AddMaxHealth()
{
	MaxHealth+=100;
	if(OnChangeHPEvent.IsBound())
		OnChangeHPEvent.Broadcast(Health/MaxHealth);
}

void UCPP_StatusComponent::SubMaxHealth()
{
	MaxHealth-=100;
	if(OnChangeHPEvent.IsBound())
		OnChangeHPEvent.Broadcast(Health/MaxHealth);
}

void UCPP_StatusComponent::SubHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	if(OnChangeHPEvent.IsBound())
		OnChangeHPEvent.Broadcast(Health/MaxHealth);
}

void UCPP_StatusComponent::SetSpeed(ESpeedType InType)
{
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed[(int32)InType];
}


void UCPP_StatusComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Health = MaxHealth;
}


