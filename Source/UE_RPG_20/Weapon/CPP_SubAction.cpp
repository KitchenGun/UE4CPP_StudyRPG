#include "CPP_SubAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"
#include "Component/CPP_StatusComponent.h"

void UCPP_SubAction::BeginPlay(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	State=CHelpers::GetComponent<UCPP_StateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCPP_StatusComponent>(OwnerCharacter);
}