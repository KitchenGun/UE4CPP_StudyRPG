
#include "Notifies/CPP_ANSEquip.h"
#include "Global.h"
#include "Weapon/CPP_WeaponComponent.h"
#include "Weapon/CPP_Equipment.h"

//FString UCPP_ANSEquip::GetNotifyName_Implementation() const
//{
//	return "Equip";
//}

void UCPP_ANSEquip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);
	//player->GetSword()->End_Equip();

	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetEquipment()->Begin_Equip();
}

void UCPP_ANSEquip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetEquipment()->End_Equip();
	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);
	//
	//player->GetSword()->End_Equip();
}
