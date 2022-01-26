
#include "CPP_DoActionCombo.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"

void UCPP_DoActionCombo::DoAction()
{
	Super::DoAction();
}

void UCPP_DoActionCombo::BeginDoAction()
{
	Super::BeginDoAction();
}

void UCPP_DoActionCombo::EndDoAction()
{
	Super::EndDoAction();
}

void UCPP_DoActionCombo::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser,InOtherCharacter);
}

void UCPP_DoActionCombo::OffAttachmentCollision()
{
	Super::OffAttachmentCollision();
}
