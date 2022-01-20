#include "Notifies/CPP_ANDead.h"
#include "Global.h"
#include "GameFramework/Character.h"

void UCPP_ANDead::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(character);

	character->Destroy();
}
