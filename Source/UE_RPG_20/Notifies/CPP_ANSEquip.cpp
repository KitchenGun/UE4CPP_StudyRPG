
#include "Notifies/CPP_ANSEquip.h"
#include "Global.h"
#include "CPP_Sword.h"
#include "Characters/CPlayer.h"

//FString UCPP_ANSEquip::GetNotifyName_Implementation() const
//{
//	return "Equip";
//}

void UCPP_ANSEquip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	player->GetSword()->Begin_Equip();
}

void UCPP_ANSEquip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	player->GetSword()->End_Equip();
}
