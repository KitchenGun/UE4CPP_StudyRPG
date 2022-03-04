
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CPP_ANHitted.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_ANHitted : public UAnimNotify
{
	GENERATED_BODY()
private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
