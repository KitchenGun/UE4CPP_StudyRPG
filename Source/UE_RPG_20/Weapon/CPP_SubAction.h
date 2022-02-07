#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_SubAction.generated.h"

UCLASS(Blueprintable)
class UE_RPG_20_API UCPP_SubAction : public UObject
{
	GENERATED_BODY()
public:
	UCPP_SubAction() {}

	virtual void BeginPlay(class ACharacter* InOwner);
	virtual void Tick(float InDeltaTime) {};
public:
	virtual void Pressed() {}
	virtual void Released() {}

	virtual void Begin_SubAction() {}
	virtual void End_SubAction() {}
public:
	UFUNCTION()
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker,class AActor* InAttackCauser,class ACharacter* InOtherCharacter) {}
	UFUNCTION()
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}
	UFUNCTION()
	virtual void OnAttachmentCollision() {}
	UFUNCTION()
	virtual void OffAttachmentCollision() {}

protected:
	class ACharacter* OwnerCharacter;
	class UWorld* World;
	class UCPP_StateComponent* State;
	class UCPP_StatusComponent* Status;
};
