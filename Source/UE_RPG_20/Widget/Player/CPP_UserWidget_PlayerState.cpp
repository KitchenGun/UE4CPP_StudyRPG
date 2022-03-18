#include "Widget/Player/CPP_UserWidget_PlayerState.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UCPP_UserWidget_PlayerState::SetLevel(int Level)
{
	Text_Level->SetText(FText::FromString(FString(TEXT("LV "))+FString::FromInt(Level)));
}

void UCPP_UserWidget_PlayerState::SetHpPercent(float percent)
{
	ProgressBar_HP->SetPercent(percent);
}

void UCPP_UserWidget_PlayerState::SetMpPercent(float percent)
{
	ProgressBar_MP->SetPercent(percent);
}

void UCPP_UserWidget_PlayerState::SetExpPercent(float percent)
{
	ProgressBar_EXP->SetPercent(percent);
}

void UCPP_UserWidget_PlayerState::NativePreConstruct()
{
	Super::NativePreConstruct();
	Text_Name->SetText(Name);
}

void UCPP_UserWidget_PlayerState::NativeConstruct()
{
	Super::NativeConstruct();

	ACPlayer* owner = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	UCPP_StatusComponent* status =CHelpers::GetComponent<UCPP_StatusComponent>(owner);
	
	status->OnChangeHPEvent.AddDynamic(this,&UCPP_UserWidget_PlayerState::SetHpPercent);
	
	
	SetLevel(1);
	SetHpPercent(1.0f);
	SetMpPercent(1.0f);
	SetExpPercent(1.0f);
}
