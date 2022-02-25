#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_PatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCPP_PatrolComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere,Category="Path")
	class ACPP_PatrolPath* Path;
	UPROPERTY(EditAnywhere,Category="Path")
	int32 NextIndex;
	UPROPERTY(EditAnywhere,Category="Path")
	bool bReverse;
	UPROPERTY(EditAnywhere,Category="Path")
	float AcceptanceDistanse =10;
public:	
	FORCEINLINE bool IsValidPath() {return Path != nullptr;}
	
	UCPP_PatrolComponent();

	bool GetMoveTo(FVector& OutLocation,float& OutAcceptanceDistance);
	void UpdateNextIndex();
	
protected:
	virtual void BeginPlay() override;

};
