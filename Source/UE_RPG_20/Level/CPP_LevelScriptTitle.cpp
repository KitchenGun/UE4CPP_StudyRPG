#include "Level/CPP_LevelScriptTitle.h"
#include "Global.h"
#include "Widget/Title/CPP_UserWidget_Title.h"

ACPP_LevelScriptTitle::ACPP_LevelScriptTitle()
{
	CHelpers::GetClass<UCPP_UserWidget_Title> (&BP_CPPWidget_Title,"WidgetBlueprint'/Game/Widget/WB_CWidget_Title.WB_CWidget_Title_C'");
}

void ACPP_LevelScriptTitle::BeginPlay()
{
	Super::BeginPlay();
	CreateWidget<UCPP_UserWidget_Title>(GetWorld(),BP_CPPWidget_Title)->AddToViewport();
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = true;
}
