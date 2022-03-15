#include "Widget/Title/CPP_UserWidget_Title.h"
#include "Global.h"
#include "Components/Button.h"
#include "../CPP_UserWidget_Controller.h"

UCPP_UserWidget_Title::UCPP_UserWidget_Title(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetClass<UCPP_UserWidget_Exit>(&Class_ExitWidget,"");
}

void UCPP_UserWidget_Title::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button_Play->OnClicked.AddDynamic(this,&UCPP_UserWidget_Title::PlayButtonClicked);
	Button_Exit->OnClicked.AddDynamic(this,&UCPP_UserWidget_Title::ExitButtonClicked);
}

void UCPP_UserWidget_Title::PlayButtonClicked()
{
	UGameplayStatics::OpenLevel(this,"PlayLevel");
}

void UCPP_UserWidget_Title::ExitButtonClicked()
{
	WidgetController->CreateClosable(Class_ExitWidget);
}


