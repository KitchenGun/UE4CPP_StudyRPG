#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_GhostTrail.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_GhostTrail : public AActor
{
	GENERATED_BODY()
private:

	UPROPERTY(EditDefaultsOnly,Category="Material")
	class UMaterialInstanceConstant* Material;
	
	UPROPERTY(EditDefaultsOnly,Category="Timer")
	float StartDelay =0;

	UPROPERTY(EditDefaultsOnly,Category="Timer")
	float Interval = 0.25f;
	
	class UPoseableMeshComponent* Poseable;//sk에서 본을 BP에서 제어하는 컴포넌트
	//pose를 저장해서 활용한다
public:	
	ACPP_GhostTrail();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	class ACharacter* OwnerCharacter;
	class UMaterialInstanceDynamic* DynamicMaterial;
private:
	FTimerHandle TimerHandle;
};
