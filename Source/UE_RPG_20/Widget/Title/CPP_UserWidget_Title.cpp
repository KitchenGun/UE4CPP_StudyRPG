#include "Widget/Title/CPP_UserWidget_Title.h"
#include "Global.h"
#include "Components/Button.h"
#include "Widget/Title/CPP_UserWidget_Exit.h"
#include "../CPP_UserWidget_Controller.h"

UCPP_UserWidget_Title::UCPP_UserWidget_Title(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer)
{
	CHelpers::GetClass<UCPP_UserWidget_Exit>(&Class_ExitWidget,"WidgetBlueprint'/Game/Widget/WB_CWidget_Exit.WB_CWidget_Exit_C'");
}

void UCPP_UserWidget_Title::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button_Play->OnClicked.AddDynamic(this,&UCPP_UserWidget_Title::PlayButtonClicked);
	Button_Exit->OnClicked.AddDynamic(this,&UCPP_UserWidget_Title::ExitButtonClicked);

	WidgetController->InitWidgetController();
}

void UCPP_UserWidget_Title::PlayButtonClicked()
{
	UGameplayStatics::OpenLevel(this,"PlayLevel");
}

void UCPP_UserWidget_Title::ExitButtonClicked()
{
	WidgetController->CreateClosable(Class_ExitWidget);
}


