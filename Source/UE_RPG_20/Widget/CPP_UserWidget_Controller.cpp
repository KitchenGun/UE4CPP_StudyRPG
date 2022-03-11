#include "Widget/CPP_UserWidget_Controller.h"
#include "Global.h"
#include "Components/CanvasPanel.h"

void UCPP_UserWidget_Controller::ResetInputMode(bool bForceChange)
{
	if(bForceChange || AllocatedClosable.Num() == 0)
	{
		switch (DefaultInputMode)
		{
		case EInputModeType::IM_GameOnly:
			PlayerController->SetInputMode(FInputModeGameOnly());
			break;
		case EInputModeType::IM_GameAndUI:
			PlayerController->SetInputMode(FInputModeGameAndUI());
			break;
		case EInputModeType::IM_UIOnly:
			PlayerController->SetInputMode(FInputModeUIOnly());
			break;
		}
	}
	
	
}

void UCPP_UserWidget_Controller::SaveWidgetPosition(const UCPP_UserWidget_Closable* closable)
{
}

void UCPP_UserWidget_Controller::InitWidgetController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	DefaultInputMode = EInputModeType::IM_GameOnly;
}

UCPP_UserWidget_Closable* UCPP_UserWidget_Controller::CreateClosable(TSubclassOf<UCPP_UserWidget_Closable> wndClass,
	bool bUsePrevPosition, EInputModeType changeInputMode, bool bShowMouseCursor, float alignmentX, float alignmentY,
	float anchorMinX, float anchorMinY, float anchorMaxX, float anchorMaxY)
{
}

void UCPP_UserWidget_Controller::CloseClosable(bool bAllClose, UCPP_UserWidget_Closable* closable)
{
}

void UCPP_UserWidget_Controller::AddChildWidget(UUserWidget* childWidget, EInputModeType changeInputMode,
	bool bShowMouseCursor, float width, float height)
{
}

void UCPP_UserWidget_Controller::closeChildWidget(UUserWidget* childWidget)
{
}

void UCPP_UserWidget_Controller::SetHighestPriorityWidget(UCPP_UserWidget_Closable* closable)
{
}
