#include "Widget/CPP_UserWidget_Closable.h"
#include "Global.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "CPP_UserWidget_Controller.h"

void UCPP_UserWidget_Closable::NativeConstruct()
{
	Super::NativeConstruct();
	SetCloseButton(CloseButton);
}

UCPP_UserWidget_Closable* UCPP_UserWidget_Closable::CreateChildClosableWidget(
	TSubclassOf<UCPP_UserWidget_Closable> widgetClass, bool bUsePrevPosition, EInputModeType changeInputMode,
	bool bShowMouseCursor)
{
	auto child = WidgetController->CreateClosable(
	widgetClass,
	bUsePrevPosition,
	changeInputMode,
	bShowMouseCursor
	);
	child->ParentWnd = this;

	ChildClosable.Add(child);

	return child;
}

void UCPP_UserWidget_Closable::SetCloseButton(UButton* closeButton)
{
	closeButton->OnClicked.AddDynamic(this,&UCPP_UserWidget_Closable::CloseThisWidget);
}

void UCPP_UserWidget_Closable::CloseThisWidget()
{
	if(bClose) return;
	WidgetController->CloseClosable(false,this);
}
void UCPP_UserWidget_Closable::CloseAllChildWidget()
{
	if(ChildClosable.Num()==0)
		return;
	for(auto child:ChildClosable)
	{
		if(IsValid(child))
		{
			if(child->bClose)
			{
				WidgetController->CloseClosable(false,child);
			}
		}		
	}
	ChildClosable.Empty();
}

void UCPP_UserWidget_Closable::DetachFromParent()
{
	if(IsValid(ParentWnd))
		ParentWnd->ChildClosable.Remove(this);
}

UCanvasPanelSlot* UCPP_UserWidget_Closable::GetCanvasPanelSlot() const
{
	return Cast<UCanvasPanelSlot>(Slot);
}

