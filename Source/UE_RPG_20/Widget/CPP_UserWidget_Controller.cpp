#include "Widget/CPP_UserWidget_Controller.h"
#include "Global.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

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

void UCPP_UserWidget_Controller::ChangeInputMode(EInputModeType inputMode)
{
	switch (inputMode)
	{
	case EInputModeType::IM_GameOnly:
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
		break;
	case EInputModeType::IM_GameAndUI:
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->bShowMouseCursor = true;
		break;
	case EInputModeType::IM_UIOnly:
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
		break;
	}
}

void UCPP_UserWidget_Controller::SaveWidgetPosition(const UCPP_UserWidget_Closable* closable)
{
	FString wndClsName = closable->GetClass()->GetName();
	FVector2D wndPosition = closable->GetCanvasPanelSlot()->GetPosition();

	
	if(PrevClosedWndPositions.Contains(wndClsName))//같은것 있으면 값 변경
		PrevClosedWndPositions[wndClsName] = wndPosition;
	else//없으면 추가
		PrevClosedWndPositions.Add(wndClsName,wndPosition);
}

void UCPP_UserWidget_Controller::InitWidgetController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	DefaultInputMode = EInputModeType::IM_GameOnly;
}

//새로운 위젯 창 생성
UCPP_UserWidget_Closable* UCPP_UserWidget_Controller::CreateClosable(TSubclassOf<UCPP_UserWidget_Closable> wndClass,
	bool bUsePrevPosition, EInputModeType changeInputMode, bool bShowMouseCursor, float alignmentX, float alignmentY,
	float anchorMinX, float anchorMinY, float anchorMaxX, float anchorMaxY)
{
	UCPP_UserWidget_Closable* newClosable = CreateWidget<UCPP_UserWidget_Closable>(this,wndClass);

	newClosable->SetWidgetController(this);

	AllocatedClosable.Add(newClosable);

	CanvasPanel_Closable->AddChild(newClosable);
	auto canvasPanelSlot = newClosable->GetCanvasPanelSlot();
	canvasPanelSlot->SetAnchors(FAnchors(anchorMinX,anchorMinY,anchorMaxX,anchorMaxY));
	canvasPanelSlot->SetAlignment(FVector2D(alignmentX,alignmentY));
	canvasPanelSlot->SetSize(newClosable->GetWndSize());
	
	if(bUsePrevPosition)
	{
		if(PrevClosedWndPositions.Contains(wndClass->GetName()))
		{
			canvasPanelSlot->SetPosition(PrevClosedWndPositions[wndClass->GetName()]);
		}
	}

	ChangeInputMode(changeInputMode);
	PlayerController->bShowMouseCursor = bShowMouseCursor;
	
	return newClosable;
}

void UCPP_UserWidget_Controller::CloseClosable(bool bAllClose, UCPP_UserWidget_Closable* closable)
{
	if(AllocatedClosable.Num() ==0)
		return;
	if(bAllClose)
	{
		for(auto elem : AllocatedClosable)
		{
			if(elem->bClose)
				continue;

			elem->bClose = true;

			if(elem->OnWndCloseEvent.IsBound())
					elem->OnWndCloseEvent.Broadcast(elem);

			elem->CloseAllChildWidget();
			SaveWidgetPosition(elem);
			elem->DetachFromParent();
			CanvasPanel_Closable->RemoveChild(elem);
		}
		AllocatedClosable.Empty();
	}
	else
	{
		closable = (closable!=nullptr) ?
			closable:
		AllocatedClosable[AllocatedClosable.Num()-1];
		
		if(!closable->bClose)
		{
			closable->bClose = true;
			if(closable->OnWndCloseEvent.IsBound())
				closable->OnWndCloseEvent.Broadcast(closable);

			AllocatedClosable.Remove(closable);

			closable->DetachFromParent();
			
			CanvasPanel_Closable->RemoveChild(closable);
		}
	}
	ResetInputMode();
}

void UCPP_UserWidget_Controller::AddChildWidget(UUserWidget* childWidget, EInputModeType changeInputMode,
	bool bShowMouseCursor, float width, float height)
{
	if(childWidget==nullptr)
		return;
	
	CanvasPanel_Closable->AddChild(childWidget);
	Cast<UCanvasPanelSlot>(childWidget->Slot)->SetSize(FVector2D(width,height));


	ChangeInputMode(changeInputMode);
	PlayerController->bShowMouseCursor = bShowMouseCursor;
	
	AllocatedWidget.Add(childWidget);
}

void UCPP_UserWidget_Controller::closeChildWidget(UUserWidget* childWidget)
{
	if(childWidget == nullptr)return;
	AllocatedWidget.Remove(childWidget);
	CanvasPanel_Closable->RemoveChild(childWidget);
	ResetInputMode();
}

void UCPP_UserWidget_Controller::SetHighestPriorityWidget(UCPP_UserWidget_Closable* closable)//최상단으로 배치하는 함수
{
	UCanvasPanelSlot* slot = closable->GetCanvasPanelSlot();
	if(CanvasPanel_Closable->GetChildIndex(closable) !=
		CanvasPanel_Closable->GetSlots().Num()-1)
	{
		FVector2D prevPostion = slot->GetPosition();
		FAnchors prevAnchors = slot->GetAnchors();
		FVector2D prevAlignment = slot->GetAlignment();
		CanvasPanel_Closable->AddChild(closable);
		
		slot = closable->GetCanvasPanelSlot();
		slot->SetAnchors(prevAnchors);
		slot->SetAlignment(prevAlignment);
		slot->SetPosition(prevPostion);
		slot->SetSize(closable->GetWndSize());
	}
}
