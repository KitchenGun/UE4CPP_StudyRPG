#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserWidget_Title.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_UserWidget_Title : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta =(BindWidget))
	class UButton* Button_Play;
	UPROPERTY(meta =(BindWidget))
	class UButton* Button_Exit;
protected:
	virtual void NativeConstruct() override;
private:
	UFUNCTION()
	void PlayButtonClicked();
	UFUNCTION()
	void ExitButtonClicked();
};
