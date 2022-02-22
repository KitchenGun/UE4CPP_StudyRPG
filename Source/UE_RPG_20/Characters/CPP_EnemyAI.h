#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CPP_EnemyAI.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_EnemyAI : public ACEnemy
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly,Category="AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly,Category="AI")
	uint8 TeamID = 2;
private:
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_BehaviorTreeComponent* Behavior;
public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() {return BehaviorTree;}
	FORCEINLINE uint8 GetTeamID() {return TeamID;}
	FORCEINLINE class UCPP_BehaviorTreeComponent* GetBehavior() {return Behavior;}
public:
	ACPP_EnemyAI();
protected:
	virtual  void BeginPlay() override;
};
