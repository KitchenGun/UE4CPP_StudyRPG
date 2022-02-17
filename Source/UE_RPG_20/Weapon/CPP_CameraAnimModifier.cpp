#include "Weapon/CPP_CameraAnimModifier.h"


void UCPP_CameraAnimModifier::ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV,
	FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV)
{
	Super::ModifyCamera(DeltaTime, ViewLocation, ViewRotation, FOV, NewViewLocation, NewViewRotation, NewFOV);

	FVector origin = ViewLocation - FVector(PlayerLocation.X,PlayerLocation.Y,0.0f);
	NewViewLocation = origin + FVector(TargetLocation.X,TargetLocation.Y,0.0f);
	
}
