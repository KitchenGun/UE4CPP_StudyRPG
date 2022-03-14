#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserWidget_DragTitle.generated.h"

DECLARE_MULTICAST_DELEGATE(FDraggingEvent)

UCLASS()
class UE_RPG_20_API UCPP_UserWidget_DragTitle : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Title Text")
	FText TitleText;

	FORCEINLINE void SetTargetWidget(UUserWidget* targetWidget)
	{TargetWidget = targetWidget;}
	FORCEINLINE class UButton* GetCloseButton()const
	{return Button_Close;}
private:
	void DragWidget();
	UFUNCTION()
	void OnWidgetDragStarted();
	UFUNCTION()
	void OnWidgetDragFinished();
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Draggable;
	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Close;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Title;
	UPROPERTY()
	bool bIsDragging;
	UPROPERTY()
	UUserWidget* TargetWidget;

public:
	FDraggingEvent OnDraggingStart;
private:
	FVector2D PrevInputPosition;
	FVector2D PrevWidgetPosition;
};
