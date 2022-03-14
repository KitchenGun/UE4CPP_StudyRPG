#include "Widget/Title/CPP_UserWidget_DragTitle.h"
#include "Global.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/PanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UCPP_UserWidget_DragTitle::NativePreConstruct()
{
	Super::NativePreConstruct();
	Text_Title->SetText(TitleText);
}

void UCPP_UserWidget_DragTitle::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Draggable->OnPressed.AddDynamic(this,&UCPP_UserWidget_DragTitle::OnWidgetDragStarted);
	Button_Draggable->OnReleased.AddDynamic(this,&UCPP_UserWidget_DragTitle::OnWidgetDragFinished);
}

void UCPP_UserWidget_DragTitle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	DragWidget();
}

void UCPP_UserWidget_DragTitle::DragWidget()
{
	if(!bIsDragging)
		return;
	if(!IsValid(TargetWidget))
		return;

	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(TargetWidget->Slot);

	slot->SetPosition(PrevWidgetPosition+(mousePosition-PrevWidgetPosition));
	
	PrevInputPosition = mousePosition;
	PrevWidgetPosition = Cast<UCanvasPanelSlot>(TargetWidget->Slot)->GetPosition();
	
}

void UCPP_UserWidget_DragTitle::OnWidgetDragStarted()
{
	if(!IsValid(TargetWidget))
		return;

	PrevInputPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	PrevWidgetPosition = Cast<UCanvasPanelSlot>(TargetWidget->Slot)->GetPosition();

	if(OnDraggingStart.IsBound())
		OnDraggingStart.Broadcast();

	
	bIsDragging = true;
}

void UCPP_UserWidget_DragTitle::OnWidgetDragFinished()
{
	if(!IsValid(TargetWidget))
		return;
	bIsDragging = false;
}

