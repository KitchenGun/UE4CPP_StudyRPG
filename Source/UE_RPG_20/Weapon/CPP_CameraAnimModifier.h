#pragma once
#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "CPP_CameraAnimModifier.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_CameraAnimModifier : public UCameraModifier
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetPlayerLocation(const FVector& InLocation) {PlayerLocation = InLocation;}
	FORCEINLINE void SetTargetLocation(const FVector& InLocation) {TargetLocation = InLocation;}
protected:
	virtual void ModifyCamera
	(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV) override;
private:
	FVector PlayerLocation;
	FVector TargetLocation;
};
