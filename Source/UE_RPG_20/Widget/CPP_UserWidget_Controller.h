#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserWidget_Closable.h"
#include "CPP_UserWidget_Controller.generated.h"

UCLASS()
	class UE_RPG_20_API UCPP_UserWidget_Controller : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* CanvasPanel_Closable;
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* CanvasPanel_Widget;
	
	void ResetInputMode(bool bForceChange=false);
	void SaveWidgetPosition(const class UCPP_UserWidget_Closable* closable);
	
public:
	void InitWidgetController();

	class UCPP_UserWidget_Closable* CreateClosable(
		TSubclassOf<UCPP_UserWidget_Closable> wndClass,bool bUsePrevPosition = false,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float alignmentX = 0.5f,float alignmentY = 0.5f,
		float anchorMinX = 0.5f,float anchorMinY =0.5f,
		float anchorMaxX = 0.5f,float anchorMaxY =0.5f);
	void CloseClosable(bool bAllClose = false,class UCPP_UserWidget_Closable* closable = nullptr);
	void AddChildWidget(class UUserWidget* childWidget,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float width = 1920.0f, float height = 1080.0f);
	void closeChildWidget(class UUserWidget* childWidget);
	void SetHighestPriorityWidget(class UCPP_UserWidget_Closable* closable);
	
private:
	class APlayerController* PlayerController;
	EInputModeType DefaultInputMode;
	
	TArray<class UCPP_UserWidget_Closable> AllocatedClosable;
	TArray<class UUserWidget*> AllocatedWidget;
	TMap<FString,FVector2D> PrevClosedWndPositions;
	
};
