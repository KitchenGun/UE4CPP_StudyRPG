#include "Notifies/CPP_ANEndDoAction.h"
#include "Global.h"
#include "CPP_Sword.h"
#include "Characters/CPlayer.h"

void UCPP_ANEndDoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	player->GetSword()->End_Action();
}