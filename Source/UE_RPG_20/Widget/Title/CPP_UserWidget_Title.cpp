#include "Widget/Title/CPP_UserWidget_Title.h"
#include "Global.h"
#include "Components/Button.h"

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
	UKismetSystemLibrary::QuitGame
	(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(),0),
		EQuitPreference::Quit,
		false
	);
}
