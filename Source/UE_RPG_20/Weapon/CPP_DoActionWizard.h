#pragma once

#include "CoreMinimal.h"
#include "Weapon/CPP_DoAction.h"
#include "CPP_DoActionWizard.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_DoActionWizard : public UCPP_DoAction
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly,Category="FireBall")
	TSubclassOf<class ACPP_Projectile> FireBallClass;
public:
	UCPP_DoActionWizard();

	virtual void BeginPlay(ACPP_Attachment* InAttachment, ACharacter* InOwner, const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas) override;

	UFUNCTION()
	virtual void DoAction() override;
	UFUNCTION()
	virtual void BeginDoAction() override;
	UFUNCTION()
	virtual void EndDoAction() override;

	virtual void OnEquip() override;
	virtual void OnUnEquip() override;
private:
	void CreateFireBall();
	UFUNCTION()
	void FireBallHit(class AActor* InCauser,class ACharacter* InOtherCharacter);
	UFUNCTION()
	void FireBallDestroy(class ACPP_Projectile* InDestroyer);
private:
	TArray<class ACPP_Projectile*> FireBalls;
};
