#include "Widget/Title/CPP_UserWidget_Exit.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UCPP_UserWidget_Exit::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(500.0f, 200.0f);
	
	Button_Yes->OnClicked.AddDynamic(this,&UCPP_UserWidget_Exit::OnYesButtonClicked);
	Button_No->OnClicked.AddDynamic(this,&UCPP_UserWidget_Exit::OnNoButtonClicked);
}

void UCPP_UserWidget_Exit::OnYesButtonClicked()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(),0),
		EQuitPreference::Quit,
		false);
}

void UCPP_UserWidget_Exit::OnNoButtonClicked()
{
	CloseThisWidget();
}
