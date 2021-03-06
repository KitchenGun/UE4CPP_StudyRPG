#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StatusComponent.h"
#include "Component/CPP_StateComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"


UCLASS()
class UE_RPG_20_API ACPlayer  : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "CameraSpeed")
		float HorizontalLook = 45;

	UPROPERTY(EditDefaultsOnly, Category = "CameraSpeed")
		float VerticalLook = 45;

	UPROPERTY(EditDefaultsOnly,Category="Team")
		uint8 TeamId =1;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;
private:
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_StatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_StateComponent* State;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_WeaponComponent* Weapon;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_WidgetComponent* Widget;
public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent, class AController* EventInstigator,AActor* DamageCauser) override;
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

	void OnOneHand();
	void OnWizard();
	void OnAction();
	void OnSubAction_Pressed();
	void OnSubAction_Released();

	UPROPERTY(EditDefaultsOnly, Category = "Sword")
	TSubclassOf<class ACPP_Sword> SwordClass;
		
	class ACPP_Sword* Sword;
public:
		FORCEINLINE class ACPP_Sword* GetSword() { return Sword; }
};
