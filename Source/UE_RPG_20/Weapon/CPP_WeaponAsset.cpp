#include "Weapon/CPP_WeaponAsset.h"
#include "Global.h"
#include "CPP_Attachment.h"
#include "CPP_Equipment.h"
#include "CPP_DoAction.h"
#include "CPP_SubAction.h"
#include "GameFramework/Character.h"

UCPP_WeaponAsset::UCPP_WeaponAsset()
{
	CHelpers::GetClass<UCPP_Equipment>(&EquipmentClass,"Blueprint'/Game/Weapons/BP_CEquipment.BP_CEquipment_C'");
	DoActionClass = UCPP_DoAction::StaticClass();
	SubActionClass = UCPP_SubAction::StaticClass();
}

void UCPP_WeaponAsset::BeginPlay(ACharacter* InOwner)
{
	if (AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		Attachment = InOwner->GetWorld()->SpawnActor<ACPP_Attachment>(AttachmentClass, params);
	}
	if (EquipmentClass)
	{
		Equipment = NewObject<UCPP_Equipment>(this, EquipmentClass);
		Equipment->BeginPlay(InOwner, EquipmentData);
		if (Attachment)
		{
			Equipment->OnEquip.AddDynamic(Attachment, &ACPP_Attachment::OnEquip);
			Equipment->OnUnEquip.AddDynamic(Attachment, &ACPP_Attachment::OnUnEquip);
		}
	}
	if (DoActionClass)
	{
		DoAction = NewObject<UCPP_DoAction>(this, DoActionClass);
		DoAction->BeginPlay(Attachment, InOwner, DoActionDatas, HitDatas);

		if (Equipment)
		{
			DoAction->SetEquipping(Equipment->IsEquipping());
			Equipment->OnEquip.AddDynamic(DoAction, &UCPP_DoAction::OnEquip);
			Equipment->OnUnEquip.AddDynamic(DoAction, &UCPP_DoAction::OnUnEquip);
		}
		if (Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCPP_DoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &UCPP_DoAction::OnAttachmentEndOverlap);

			Attachment->OnAttachmentCollision.AddDynamic(DoAction, &UCPP_DoAction::OnAttachmentCollision);
			Attachment->OffAttachmentCollision.AddDynamic(DoAction, &UCPP_DoAction::OffAttachmentCollision);
		}
	}
	if (SubActionClass)
	{
		SubAction = NewObject<UCPP_SubAction>(this, SubActionClass);
		SubAction->BeginPlay(InOwner);

		if (Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(SubAction, &UCPP_SubAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(SubAction, &UCPP_SubAction::OnAttachmentEndOverlap);

			Attachment->OnAttachmentCollision.AddDynamic(SubAction, &UCPP_SubAction::OnAttachmentCollision);
			Attachment->OffAttachmentCollision.AddDynamic(SubAction, &UCPP_SubAction::OffAttachmentCollision);
		}
	}
}

void UCPP_WeaponAsset::EndPlay()
{
	

}
