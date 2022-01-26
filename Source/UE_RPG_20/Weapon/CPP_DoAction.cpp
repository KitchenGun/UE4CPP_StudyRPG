#include "Weapon/CPP_DoAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"

UCPP_DoAction::UCPP_DoAction()
{

}

void UCPP_DoAction::BeginPlay(ACPP_Attachment* InAttachment, ACharacter* InOwner, const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas)
{
	ActionDatas = InActionDatas;
	HitDatas= InHitDatas;

	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();
	State=CHelpers::GetComponent<UCPP_StateComponent>(OwnerCharacter);
}
