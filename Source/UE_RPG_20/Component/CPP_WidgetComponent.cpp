#include "Component/CPP_WidgetComponent.h"
#include "Global.h"
#include "Widget/CPP_UserWidget_Controller.h"
#include "Widget/CPP_UserWidget_Closable.h"
#include "Widget/Player/CPP_UserWidget_PlayerState.h"
#include "Widget/Player/CPP_UserWidget_Player.h"
#include "Widget/Player/Status/CPP_UserWidget_Status.h"

UCPP_WidgetComponent::UCPP_WidgetComponent()
{
	CHelpers::GetClass<UCPP_UserWidget_Controller>(&WidgetControllerClass,"WidgetBlueprint'/Game/Widget/WB_CWidget_Controller.WB_CWidget_Controller_C'");
	CHelpers::GetClass<UCPP_UserWidget_Player>(&WidgetPlayerStateClass,"WidgetBlueprint'/Game/Widget/Player/WB_CWidget_Player.WB_CWidget_Player_C'");
	CHelpers::GetClass<UCPP_UserWidget_Status>(&StatusWidgetClass,"WidgetBlueprint'/Game/Widget/Player/Status/WB_CWidget_Status.WB_CWidget_Status_C'");
}


void UCPP_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
	WidgetController = CreateWidget<UCPP_UserWidget_Controller>(playerController,WidgetControllerClass);
	WidgetController->InitWidgetController();
	WidgetController->AddToViewport();

	Widget_Player = CreateWidget<UCPP_UserWidget_Player>(playerController,WidgetPlayerStateClass);
	
	WidgetController->AddChildWidget(Widget_Player,EInputModeType::IM_GameOnly,false);
}

void UCPP_WidgetComponent::OpenStatus()
{
	if(IsValid(StatusWidget))
		return;
	
	StatusWidget = Cast<UCPP_UserWidget_Status>(WidgetController->CreateClosable(
		StatusWidgetClass,true,EInputModeType::IM_GameAndUI
	));
	//람다 -> closable 전달해주는 것으로 현재 아무것도 안하고있음
	StatusWidget->OnWndCloseEvent.AddLambda([this](class UCPP_UserWidget_Closable* closable)
		{StatusWidget = nullptr;});
}

void UCPP_WidgetComponent::CloseStatus()
{
	if(IsValid(StatusWidget))
	{
		StatusWidget->CloseThisWidget();
		StatusWidget = nullptr;
	}
}

void UCPP_WidgetComponent::ToggleStatus()
{
	UE_LOG(LogTemp,Display,L"input");
	if(IsValid(StatusWidget))
		CloseStatus();
	else
	{
		OpenStatus();
	}
}


