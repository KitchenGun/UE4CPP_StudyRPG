#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CPP_ANSCameraAnim.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_ANSCameraAnim : public UAnimNotifyState
{
	GENERATED_BODY()
private:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	class UCPP_CameraAnimModifier* Modifier;
};
