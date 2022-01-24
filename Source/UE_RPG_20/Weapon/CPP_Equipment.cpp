#include "Weapon/CPP_Equipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/CPP_StateComponent.h"
#include "Component/CPP_StatusComponent.h"

#include "CPP_Equipment.h"

UCPP_Equipment::UCPP_Equipment()
{

}

void UCPP_Equipment::BeginPlay(ACharacter* InOwner, const FEquipmentData& InData)
{
	OwnerCharacter = InOwner;
	Data = InData;
	State = CHelpers::GetComponent<UCPP_StateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCPP_StatusComponent>(OwnerCharacter);
}

void UCPP_Equipment::Equip_Implementation()
{
	State->SetEquipMode();

	if(!Data.bCanMove) Status->Stop();
	if(Data.Montage) OwnerCharacter->PlayAnimMontage(Data.Montage,Data.PlayRatio);
	else
	{
		Begin_Equip();
		End_Equip();
	}
	if (Data.bLookForward)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}


void UCPP_Equipment::Begin_Equip_Implementation()
{
	if(OnEquip().IsBound())
		OnEquip().Broadcast();

}


void UCPP_Equipment::End_Equip_Implementation()
{
	State->SetIdleMode();
	Status->Move();
	bEquipping = true;
}

void UCPP_Equipment::UnEquip_Implementation()
{
bEquipping = false;
	OwnerCharacter->bUseControllerRotationYaw=false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	if(OnUnEquip().IsBound())
		OnUnEquip().Broadcast();
}
