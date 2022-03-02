#include "Weapon/CPP_WeaponAsset.h"
#include "Global.h"
#include "CPP_Attachment.h"
#include "CPP_Equipment.h"
#include "CPP_DoAction.h"
#include "CPP_SubAction.h"
#include "CPP_WeaponData.h"
#include "GameFramework/Character.h"

UCPP_WeaponAsset::UCPP_WeaponAsset()
{
	CHelpers::GetClass<UCPP_Equipment>(&EquipmentClass,"Blueprint'/Game/Weapons/BP_CEquipment.BP_CEquipment_C'");
	DoActionClass = UCPP_DoAction::StaticClass();
	SubActionClass = UCPP_SubAction::StaticClass();
}

void UCPP_WeaponAsset::BeginPlay(ACharacter* InOwner,class UCPP_WeaponData** OutAction)
{
	ACPP_Attachment* attachment = nullptr;
	
	if (AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		attachment = InOwner->GetWorld()->SpawnActor<ACPP_Attachment>(AttachmentClass, params);
	}
	UCPP_Equipment* equipment= nullptr;
	if (EquipmentClass)
	{
		equipment = NewObject<UCPP_Equipment>(this, EquipmentClass);
		equipment->BeginPlay(InOwner, EquipmentData);
		if (attachment)
		{
			equipment->OnEquip.AddDynamic(attachment, &ACPP_Attachment::OnEquip);
			equipment->OnUnEquip.AddDynamic(attachment, &ACPP_Attachment::OnUnEquip);
		}
	}
	UCPP_DoAction* doAction= nullptr;
	if (DoActionClass)
	{
		doAction = NewObject<UCPP_DoAction>(this, DoActionClass);
		doAction->BeginPlay(attachment, InOwner, DoActionDatas, HitDatas);

		if (equipment)
		{
			doAction->SetEquipping(equipment->IsEquipping());
			equipment->OnEquip.AddDynamic(doAction, &UCPP_DoAction::OnEquip);
			equipment->OnUnEquip.AddDynamic(doAction, &UCPP_DoAction::OnUnEquip);
		}
		if (attachment)
		{
			attachment->OnAttachmentBeginOverlap.AddDynamic(doAction, &UCPP_DoAction::OnAttachmentBeginOverlap);
			attachment->OnAttachmentEndOverlap.AddDynamic(doAction, &UCPP_DoAction::OnAttachmentEndOverlap);

			attachment->OnAttachmentCollision.AddDynamic(doAction, &UCPP_DoAction::OnAttachmentCollision);
			attachment->OffAttachmentCollision.AddDynamic(doAction, &UCPP_DoAction::OffAttachmentCollision);
		}
	}
	UCPP_SubAction* subAction = nullptr;
	if (SubActionClass)
	{
		subAction = NewObject<UCPP_SubAction>(this, SubActionClass);
		subAction->BeginPlay(InOwner);

		if (attachment)
		{
			attachment->OnAttachmentBeginOverlap.AddDynamic(subAction, &UCPP_SubAction::OnAttachmentBeginOverlap);
			attachment->OnAttachmentEndOverlap.AddDynamic(subAction, &UCPP_SubAction::OnAttachmentEndOverlap);

			attachment->OnAttachmentCollision.AddDynamic(subAction, &UCPP_SubAction::OnAttachmentCollision);
			attachment->OffAttachmentCollision.AddDynamic(subAction, &UCPP_SubAction::OffAttachmentCollision);
		}
	}
	*OutAction = NewObject<UCPP_WeaponData>();
	(*OutAction)->Attachment = attachment;
	(*OutAction)->Equipment = equipment;
	(*OutAction)->DoAction = doAction;
	(*OutAction)->SubAction = subAction;
}

void UCPP_WeaponAsset::EndPlay()
{
	

}
