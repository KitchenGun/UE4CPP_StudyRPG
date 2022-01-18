#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Component/CPP_StatusComponent.h"
#include "Component/CPP_StateComponent.h"
#include "Animation/AnimMontage.h"
#include "CPP_Sword.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_Sword : public AActor
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
	class USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly)
	class UCapsuleComponent* Capsule;
private:
	class ACharacter* OwnerCharacter;
	class UCPP_StateComponent* State;
	class UCPP_StatusComponent* Status;

	bool bEquipped = false;
private:
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* EquipMontage;

public:	
	ACPP_Sword();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void UnEquip();

	void OnCollision();
	void OffCollision();

	FORCEINLINE bool GetEquipped() const { return bEquipped; }
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
