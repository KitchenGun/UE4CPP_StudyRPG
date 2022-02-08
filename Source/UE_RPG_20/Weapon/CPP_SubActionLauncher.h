#pragma once

#include "CoreMinimal.h"
#include "Weapon/CPP_SubAction.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapon/CPP_WeaponStructures.h"
#include "CPP_SubActionLauncher.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_SubActionLauncher : public UCPP_SubAction
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float Distance = 1000;
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float Speed = 200;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	FDoActionData ActionData;
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	FHitData HitData;

public:
	UCPP_SubActionLauncher();

	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void Tick(float InDeltaTime) override;

	virtual void Begin_SubAction() override;
	virtual void End_SubAction() override;
public:
	virtual void Pressed() override;

	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OffAttachmentCollision() override;
private :
	bool bMoving;
	FVector Start;
	FVector End;

	float OwnerRadius;

	TArray<class ACharacter*> Overlapped;
	TArray<class ACharacter*> Hitted;
};
