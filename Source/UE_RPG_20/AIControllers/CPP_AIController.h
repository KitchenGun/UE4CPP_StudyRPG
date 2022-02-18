#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "CPP_AIController.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_AIController : public AAIController
{
	GENERATED_BODY()
public:
	ACPP_AIController();
private:
	UPROPERTY(EditAnywhere)
	class UAISenseConfig_Sight* SightSense;
	
	
	
};
