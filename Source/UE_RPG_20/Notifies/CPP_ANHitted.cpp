
#include "Notifies/CPP_ANHitted.h"
#include "Global.h"
#include "Component/CPP_StateComponent.h"
#include "GameFramework/Character.h"


void UCPP_ANHitted::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(character);

	UCPP_StateComponent* state = CHelpers::GetComponent<UCPP_StateComponent>(character);
	if(state)
		state->SetIdleMode();
}
