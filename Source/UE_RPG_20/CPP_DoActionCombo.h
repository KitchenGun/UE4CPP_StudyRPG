#pragma once

#include "CoreMinimal.h"
#include "Weapon/CPP_DoAction.h"
#include "CPP_DoActionCombo.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_DoActionCombo : public UCPP_DoAction
{
	GENERATED_BODY()
public:

	virtual void DoAction() override;
	virtual void BeginDoAction() override;
	virtual void EndDoAction() override;

public:
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;

	virtual void OffAttachmentCollision() override;
private:
	int32 Index;

	bool bEnable;
	bool bExist;

	int32 HitIndex;
	TArray<class ACharacter*> Hitted;
};
