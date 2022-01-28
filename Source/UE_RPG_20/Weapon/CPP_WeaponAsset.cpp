#include "Weapon/CPP_WeaponAsset.h"
#include "Global.h"
#include "CPP_Attachment.h"
#include "CPP_Equipment.h"
#include "CPP_DoAction.h"
#include "GameFramework/Character.h"

UCPP_WeaponAsset::UCPP_WeaponAsset()
{
	EquipmentClass = 
	DoActionClass = 
}

void UCPP_WeaponAsset::BeginPlay(ACharacter* InOwner)
{
	if (AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;
		Attachment = InOwner->GetWorld()->SpawnActor<ACPP_Attachment>(AttachmentClass,params);
	}
	if (EquipmentClass)
	{
		Equipment = NewObject<UCPP_Equipment>(this,EquipmentClass);
		if (Attachment)
		{
			Equipment->OnEquip.AddDynamic(Attachment,&ACPP_Attachment::OnEquip);
			Equipment->OnUnEquip.AddDynamic(Attachment,&ACPP_Attachment::OnUnEquip);
		}
	}
	if (DoActionClass)
	{
		DoAction = NewObject<UCPP_DoAction>(this,DoActionClass);
		DoAction->BeginPlay(Attachment,InOwner,DoActionDatas,HitDatas);

		if(Equipment)
		{
			DoAction->SetEquipping(Equipment->IsEquipping());
			Equipment->OnEquip.AddDynamic(DoAction,&UCPP_DoAction::OnEquip);
			Equipment->OnEquip.AddDynamic(DoAction, &UCPP_DoAction::OnUnEquip);
		}
		if (Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction,&UCPP_DoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction,&UCPP_DoAction::OnAttachmentEndOverlap);
		}
	}

}

void UCPP_WeaponAsset::EndPlay()
{
}
