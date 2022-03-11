#include "Widget/CPP_UserWidget_Closable.h"
#include "Global.h"
#include "Components/Button.h"

void UCPP_UserWidget_Closable::NativeConstruct()
{
	Super::NativeConstruct();
	SetCloseButton(CloseButton);
}

UCPP_UserWidget_Closable* UCPP_UserWidget_Closable::CreateChildClosableWidget(
	TSubclassOf<UCPP_UserWidget_Closable> widgetClass, bool bUsePrevPosition, EInputModeType changeInputMode,
	bool bShowMouseCursor)
{
	
}

void UCPP_UserWidget_Closable::SetCloseButton(UButton* closeButton)
{
	closeButton->OnClicked.AddDynamic(this,&UCPP_UserWidget_Closable::CloseThisWidget);
}

void UCPP_UserWidget_Closable::CloseThisWidget()
{
	
}
void UCPP_UserWidget_Closable::CloseAllChildWidget()
{

}

