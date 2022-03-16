#include "Component/CPP_WidgetComponent.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Widget/CPP_UserWidget_Controller.h"
#include "Widget/CPP_UserWidget_Closable.h"

UCPP_WidgetComponent::UCPP_WidgetComponent()
{
	CHelpers::GetClass<UCPP_UserWidget_Controller>(&WidgetControllerClass,"WidgetBlueprint'/Game/Widget/WB_CWidget_Controller.WB_CWidget_Controller_C'");
}


void UCPP_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
	WidgetController = CreateWidget<UCPP_UserWidget_Controller>(playerController,WidgetControllerClass);
	WidgetController->InitWidgetController();
	WidgetController->AddToViewport();
}


