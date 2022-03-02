#include "Weapon/CPP_WeaponComponent.h"

#include "CPP_SubAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapon/CPP_DoAction.h"
#include "Weapon/CPP_SubAction.h"
#include "Weapon/CPP_WeaponData.h"
#include "Weapon/CPP_WeaponAsset.h"


UCPP_WeaponComponent::UCPP_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCPP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		if(DataAssets[i])
			DataAssets[i]->BeginPlay(OwnerCharacter,&Datas[i]);
	}
}


void UCPP_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsUnarmedMode() == false)
	{
		if (GetDoAction())
			GetDoAction()->Tick(DeltaTime);

		if (GetSubAction())
			GetSubAction()->Tick(DeltaTime);
	}
}

ACPP_Attachment* UCPP_WeaponComponent::GetAttachment()
{
	return Datas[(int32)Type]->GetAttachment();
}

UCPP_Equipment* UCPP_WeaponComponent::GetEquipment()
{
	return Datas[(int32)Type]->GetEquipment();
}

UCPP_DoAction* UCPP_WeaponComponent::GetDoAction()
{
	return Datas[(int32)Type]->GetDoAction();
}

UCPP_SubAction* UCPP_WeaponComponent::GetSubAction()
{
	return Datas[(int32)Type]->GetSubAction();	
}


void UCPP_WeaponComponent::SetMode(EWeaponType InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();
		return;
	}
	else if (IsUnarmedMode() == false)
	{
		GetEquipment()->UnEquip();
	}

	if (DataAssets[(int32)InType])
	{
		Datas[(int32)InType]->GetEquipment()->Equip();
		ChangeType(InType);
	}
}

void UCPP_WeaponComponent::ChangeType(EWeaponType InType)
{
	Type = InType;
	if(OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(InType);
}

void UCPP_WeaponComponent::SetUnarmedMode()
{
	GetEquipment()->UnEquip();
	ChangeType(EWeaponType::Max);
}

void UCPP_WeaponComponent::SetFistMode()
{
	SetMode(EWeaponType::Fist);
}

void UCPP_WeaponComponent::SetOneHandMode()
{
	SetMode(EWeaponType::OneHand);
}

void UCPP_WeaponComponent::SetTwoHandMode()
{
	SetMode(EWeaponType::TwoHand);
}

void UCPP_WeaponComponent::SetWarpMode()
{
	SetMode(EWeaponType::Warp);
}

void UCPP_WeaponComponent::SetWizardMode()
{
	SetMode(EWeaponType::Wizard);
}


void UCPP_WeaponComponent::SetBowMode()
{
	SetMode(EWeaponType::Bow);
}

void UCPP_WeaponComponent::DoAction()
{
	CheckTrue(Type == EWeaponType::Max);
	GetDoAction()->DoAction();
}

void UCPP_WeaponComponent::SubAction_Pressed()
{
	CheckTrue(Type == EWeaponType::Max);
	GetSubAction()->Pressed();
}

void UCPP_WeaponComponent::SubAction_Released()
{
	CheckTrue(Type == EWeaponType::Max);
	GetSubAction()->Released();
}



