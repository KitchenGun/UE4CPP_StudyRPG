#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Projectile.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_Projectile : public AActor
{
	GENERATED_BODY()
public:	
	ACPP_Projectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
