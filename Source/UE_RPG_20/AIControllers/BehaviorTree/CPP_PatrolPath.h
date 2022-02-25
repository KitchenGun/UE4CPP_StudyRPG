
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_PatrolPath.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_PatrolPath : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere,Category = "Loop")
	bool bLoop;
	
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
	class USplineComponent* Spline;
	UPROPERTY(VisibleDefaultsOnly)
	class UTextRenderComponent* Text;
public:
	FORCEINLINE class USplineComponent* GetSpline() {return Spline;}
	ACPP_PatrolPath();
	//에디터에서 만든 클래스를 배치했을때 호출되는 함수
	virtual  void OnConstruction(const FTransform& Transform) override;
	
protected:
	virtual void BeginPlay() override;

};
