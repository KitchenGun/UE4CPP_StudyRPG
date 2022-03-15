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
	UPROPERTY(meta=(BindWidget))
	class UCPP_UserWidget_Controller* WidgetController;

private:
	TSubclassOf<class UCPP_UserWidget_Exit> Class_ExitWidget;
	
public:
	UCPP_UserWidget_Title(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeConstruct() override;
private:
	UFUNCTION()
	void PlayButtonClicked();
	UFUNCTION()
	void ExitButtonClicked();
};
