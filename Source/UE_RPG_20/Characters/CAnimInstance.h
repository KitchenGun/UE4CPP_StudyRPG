#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapon/CPP_WeaponComponent.h"
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
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
	//	bool bEquipped;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "WeaponType")
	EWeaponType WeaponType = EWeaponType::Max;
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnWeaponTypeChanged(EWeaponType InNewType);
private:
	class ACharacter* OwnerCharacter;
	class UCPP_WeaponComponent* Weapon;
};
