#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class UE_RPG_20_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Pitch;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
		bool bEquipped;
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACharacter* OwnerCharacter;
};
