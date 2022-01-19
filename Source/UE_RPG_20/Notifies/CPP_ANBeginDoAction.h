#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CPP_ANBeginDoAction.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_ANBeginDoAction : public UAnimNotify
{
	GENERATED_BODY()
private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};