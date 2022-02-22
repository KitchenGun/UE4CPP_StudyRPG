#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CPP_BTService_Melee.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_BTService_Melee : public UBTService
{
	GENERATED_BODY()
public:
	UCPP_BTService_Melee();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

private:
	UPROPERTY(EditAnywhere, Category="Action")
	float ActionRange = 150;
	
};
