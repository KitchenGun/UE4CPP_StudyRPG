#include "Widget/Player/Status/CPP_UserWidget_PlayerStatusRow.h"
#include "Global.h"
#include "Components/Image.h"
#include "Engine/AssetManager.h"//에셋들을 관리해준다   비동기 로드
#include "Engine/StreamableManager.h"//에셋 매니져에서 관리하는 것을 로드해줄때 
#include "Components/TextBlock.h"
#include "Components/Button.h"

//동기 로드
//결과가 끝날때까지 진행 //큰데이터들은 하지 않는 것을 추천 하지만 빠르다  실행중인 쓰레드만 멈춤
//비동기 로드
//결과가 끝나지 않더라도 진행 

void UCPP_UserWidget_PlayerStatusRow::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Plus->OnClicked.AddDynamic(this,&UCPP_UserWidget_PlayerStatusRow::OnPlusButtonClicked);
	Button_Minus->OnClicked.AddDynamic(this,&UCPP_UserWidget_PlayerStatusRow::OnMinusButtonClicked);
}

void UCPP_UserWidget_PlayerStatusRow::InitializeRow(FStatusRowData data)
{
	Text_StatName->SetText(data.Stat);
	UTexture2D* image = Cast<UTexture2D>(UAssetManager::GetStreamableManager().LoadSynchronous(data.StatImage));
	Image_Icon->SetBrushFromTexture(image);
	
}

void UCPP_UserWidget_PlayerStatusRow::OnPlusButtonClicked()
{
	if(OnPlusButtonEvent.IsBound())
		OnPlusButtonEvent.Broadcast();
	++Stat;
	Text_Stat->SetText(FText::FromString(FString::FromInt(Stat)));
}

void UCPP_UserWidget_PlayerStatusRow::OnMinusButtonClicked()
{
	if(OnMinusButtonEvent.IsBound())
		OnMinusButtonEvent.Broadcast();
	--Stat;
	Text_Stat->SetText(FText::FromString(FString::FromInt(Stat)));
}
