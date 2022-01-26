#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_WeaponStructures.h"
#include "CPP_DoAction.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_DoAction : public UObject
{
	GENERATED_BODY()
public:
	UCPP_DoAction();

	//»ó¼Ó¿ë
	virtual void BeginPlay(class ACPP_Attachment* InAttachment,class ACharacter* InOwner,const TArray<FDoActionData>& InActionDatas,const TArray<FHitData>& InHitDatas);
public:
	virtual void DoAction() {}
	virtual void BeginDoAction() {}
	virtual void EndDoAction() {}
	
	virtual void Tick(float InDeltaTime) {};

	UFUNCTION()
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker,class AActor* InAttackCauser,class ACharacter* InOtherCharacter) {}

	UFUNCTION()
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
	virtual void OffAttachmentCollision() {}

	UFUNCTION()
	virtual void OnEquip() {}

	UFUNCTION()
	virtual void OnUnEquip() {}
protected:
	class ACharacter* OwnerCharacter;
	class UWorld* World;

	class UCPP_StateComponent* State;

	TArray<FDoActionData> ActionDatas;
	TArray<FHitData> HitDatas;

	const bool* bEquipping;
public:
	FORCEINLINE void SetEquipping(const bool* InEquipping){bEquipping = InEquipping;}
};
