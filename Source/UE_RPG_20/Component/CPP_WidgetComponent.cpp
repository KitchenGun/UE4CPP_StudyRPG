#include "Component/CPP_WidgetComponent.h"
#include "Global.h"
#include "Widget/CPP_UserWidget_Controller.h"
#include "Widget/CPP_UserWidget_Closable.h"
#include "Widget/Player/CPP_UserWidget_PlayerState.h"
#include "Widget/Player/CPP_UserWidget_Player.h"


UCPP_WidgetComponent::UCPP_WidgetComponent()
{
	CHelpers::GetClass<UCPP_UserWidget_Controller>(&WidgetControllerClass,"WidgetBlueprint'/Game/Widget/WB_CWidget_Controller.WB_CWidget_Controller_C'");
	CHelpers::GetClass<UCPP_UserWidget_Player>(&WidgetPlayerStateClass,"WidgetBlueprint'/Game/Widget/Player/WB_CWidget_PlayerState.WB_CWidget_PlayerState_C'");
}


void UCPP_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
	WidgetController = CreateWidget<UCPP_UserWidget_Controller>(playerController,WidgetControllerClass);
	WidgetController->InitWidgetController();
	WidgetController->AddToViewport();

	Widget_Player = CreateWidget<UCPP_UserWidget_Player>(playerController,WidgetPlayerStateClass);
	
	WidgetController->AddChildWidget(Widget_Player,EInputModeType::IM_GameOnly,false,
		500.0f,210.0f);
}


