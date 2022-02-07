#include "CPP_SubAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"
#include "Component/CPP_StatusComponent.h"

void UCPP_SubAction::BeginPlay(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	CHelpers::GetComponent<UCPP_StateComponent>(OwnerCharacter);
	CHelpers::GetComponent<UCPP_StatusComponent>(OwnerCharacter);
}