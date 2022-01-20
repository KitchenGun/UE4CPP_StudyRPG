#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Component/CPP_StateComponent.h"
#include "Component/CPP_MontageComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class UE_RPG_20_API ACEnemy : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly,Category ="Color")
	FLinearColor OriginColor = FLinearColor::Black;


private:
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_MontageComponent* Montage;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_StatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_StateComponent* State;
public:
	ACEnemy();

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent, class AController* EventInstigator,AActor* DamageCauser) override;
protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InType);

	void Change_Character_Color(FLinearColor InColor);
	void Hitted();
	void Dead();
private:

	struct FDamaged
	{
		float DamageAmount;
		class AController* EventInstigator;
	}Damaged;

	TArray<class UMaterialInstanceDynamic*> Materials;
};
