#include "Notifies/CPP_ANSCombo.h"
#include "Global.h"
#include "Weapon/CPP_WeaponComponent.h"
#include "Weapon/CPP_DoActionCombo.h"

void UCPP_ANSCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	UCPP_DoActionCombo* combo = Cast<UCPP_DoActionCombo>(weapon->GetDoAction());
	

	combo->Enable_Combo();
	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);
	//
	//player->GetSword()->Enable_Combo();
}

void UCPP_ANSCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());


	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	UCPP_DoActionCombo* combo = Cast<UCPP_DoActionCombo>(weapon->GetDoAction());
	combo->Disable_Combo();
	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);
	//
	//player->GetSword()->Disable_Combo();
}
