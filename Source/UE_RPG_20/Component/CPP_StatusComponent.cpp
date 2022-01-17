#include "Component/CPP_StatusComponent.h"

// Sets default values for this component's properties
UCPP_StatusComponent::UCPP_StatusComponent()
{
}

void UCPP_StatusComponent::AddHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void UCPP_StatusComponent::SubHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}


void UCPP_StatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}


