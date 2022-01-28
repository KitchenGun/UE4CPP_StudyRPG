#include "Weapon/CPP_WeaponComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapon/CPP_DoAction.h"
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
			DataAssets[i]->BeginPlay(OwnerCharacter);
	}
}


void UCPP_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsUnarmedMode() == false)
	{
		if(GetDoAction())
			GetDoAction()->Tick(DeltaTime);
	}
}

ACPP_Attachment* UCPP_WeaponComponent::GetAttachment()
{
	return DataAssets[(int32)Type]->GetAttachment();
}

UCPP_Equipment* UCPP_WeaponComponent::GetEquipment()
{
	return DataAssets[(int32)Type]->GetEquipment();
}

UCPP_DoAction* UCPP_WeaponComponent::GetDoAction()
{
	return DataAssets[(int32)Type]->GetDoAction();
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
		DataAssets[(int32)InType]->GetEquipment()->Equip();
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
	SetMode(EWeaponType::Max);
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

void UCPP_WeaponComponent::SetFireStormMode()
{
	SetMode(EWeaponType::FireStorm);
}

void UCPP_WeaponComponent::SetIceBallMode()
{
	SetMode(EWeaponType::IceBall);
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


