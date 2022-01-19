#include "Notifies/CPP_ANBeginDoAction.h"
#include "Global.h"
#include "CPP_Sword.h"
#include "Characters/CPlayer.h"

void UCPP_ANBeginDoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	player->GetSword()->Begin_Action();
}

