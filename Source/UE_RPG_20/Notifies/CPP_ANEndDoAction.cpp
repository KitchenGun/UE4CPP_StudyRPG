#include "Notifies/CPP_ANEndDoAction.h"
#include "Global.h"
#include "Weapon/CPP_WeaponComponent.h"
#include "Weapon/CPP_DoAction.h"

void UCPP_ANEndDoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetDoAction()->EndDoAction();

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);
	//
	//player->GetSword()->End_Action();
}