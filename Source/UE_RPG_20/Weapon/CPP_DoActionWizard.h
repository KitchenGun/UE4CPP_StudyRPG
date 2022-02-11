#pragma once

#include "CoreMinimal.h"
#include "Weapon/CPP_DoAction.h"
#include "CPP_DoActionWizard.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_DoActionWizard : public UCPP_DoAction
{
	GENERATED_BODY()
private:
	TSubclassOf<class ACPP_Projectile> ProjectileClass;
public:
	UCPP_DoActionWizard();

	virtual void BeginPlay(ACPP_Attachment* InAttachment, ACharacter* InOwner, const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas) override;
	virtual void Tick(float InDeltaTime) override;

	UFUNCTION()
	virtual void DoAction() override;
	UFUNCTION()
	virtual void BeginDoAction() override;
	UFUNCTION()
	virtual void EndDoAction() override;

	UFUNCTION()
	void OnFireballBeginOverlap(AActor* InAttackCauser, ACharacter* InOtherCharacter);
};
