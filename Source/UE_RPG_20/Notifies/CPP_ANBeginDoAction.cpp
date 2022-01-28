#include "Notifies/CPP_ANBeginDoAction.h"
#include "Weapon/CPP_WeaponComponent.h"
#include "Weapon/CPP_DoAction.h"
#include "Global.h"

void UCPP_ANBeginDoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetDoAction()->BeginDoAction();

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);

	//player->GetSword()->Begin_Action();
}

