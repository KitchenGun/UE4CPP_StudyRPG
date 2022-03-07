
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserWidget_Health.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_UserWidget_Health : public UUserWidget
{
	GENERATED_BODY()
public :
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealth(float InHealth,float InMaxHealth);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCharacterName(const FString& InName);
	
};
