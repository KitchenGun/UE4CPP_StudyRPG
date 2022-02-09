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
	
	class UPoseableMeshComponent* Poseable;//sk���� ���� BP���� �����ϴ� ������Ʈ
	//pose�� �����ؼ� Ȱ���Ѵ�
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
