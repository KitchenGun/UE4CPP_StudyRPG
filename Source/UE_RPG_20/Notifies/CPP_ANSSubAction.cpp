
#include "Notifies/CPP_ANSSubAction.h"
#include "Global.h"
#include "Weapon/CPP_WeaponComponent.h"
#include "Weapon/CPP_SubAction.h"

void UCPP_ANSSubAction::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetSubAction()->Begin_SubAction();
}

void UCPP_ANSSubAction::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetSubAction()->End_SubAction();
}
