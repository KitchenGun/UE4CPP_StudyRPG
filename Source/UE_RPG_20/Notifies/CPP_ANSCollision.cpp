#include "Notifies/CPP_ANSCollision.h"
#include "Global.h"
#include "Weapon/CPP_WeaponComponent.h"
#include "Weapon/CPP_Attachment.h"

void UCPP_ANSCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());


	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetAttachment()->OnCollision();

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);
	//
	//player->GetSword()->OnCollision();
}

void UCPP_ANSCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());


	UCPP_WeaponComponent* weapon = CHelpers::GetComponent<UCPP_WeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetAttachment()->OffCollision();
	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);
	//
	//player->GetSword()->OffCollision();
}
