#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserWidget_Closable.generated.h"

UENUM()
enum class EInputModeType : uint8
{
	IM_Defalut,IM_GameOnly,IM_UIOnly,IM_GameAndUI
};

DECLARE_MULTICAST_DELEGATE_OneParam(FWndEventSignature,class UCPP_UserWidget_Closable*)


UCLASS()
class UE_RPG_20_API UCPP_UserWidget_Closable : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UCPP_UserWidget_Closable* ParentWnd;

	UPROPERTY()
	bool bClose;
	
	UFUNCTION()
	void CloseThisWidget();
	UFUNCTION()
	UCPP_UserWidget_Closable* CreateChildClosableWidget(
		TSubclassOf<UCPP_UserWidget_Closable> widgetClass,
		bool bUsePrevPosition = false,
		EInputModeType changeInputMode=EInputModeType::IM_Defalut,
		bool bShowMouseCursor = true);


	void SetCloseButton(class UButton* closeButton);
	void CloseAllChildWidget();

	void DetachFromParent();
	
public:
	class UCanvasPanelSlot* GetCanvasPanelSlot() const;
	FORCEINLINE void SetWidgetController(class UCPP_UserWidget_Controller* widgetController)
	{WidgetController = widgetController;}
	FORCEINLINE FVector2D GetWndSize() const {return WndSize;}
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta =(BindWidget))
	class UButton* CloseButton;
private:
	UPROPERTY(meta=(BindWidget))
	class UCPP_UserWidget_DragTitle* DragTitle;
	

	
public:
	FWndEventSignature OnWndCloseEvent;
protected:
	FVector2D WndSize;
private:
	class UCPP_UserWidget_Controller* WidgetController;

	TArray<UCPP_UserWidget_Closable*> ChildClosable;
};
