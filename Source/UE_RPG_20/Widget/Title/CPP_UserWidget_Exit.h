#pragma once

#include "CoreMinimal.h"
#include "Widget/CPP_UserWidget_Closable.h"
#include "CPP_UserWidget_Exit.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_UserWidget_Exit : public UCPP_UserWidget_Closable
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Yes;
	UPROPERTY(meta=(BindWidget))
	class UButton* Button_No;

protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void OnYesButtonClicked();
	UFUNCTION()
	void OnNoButtonClicked();
	
};
