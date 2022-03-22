#include "Widget/Player/Status/CPP_UserWidget_PlayerStatusRow.h"
#include "Global.h"
#include "Components/Image.h"
#include "Engine/AssetManager.h"//���µ��� �������ش�   �񵿱� �ε�
#include "Engine/StreamableManager.h"//���� �Ŵ������� �����ϴ� ���� �ε����ٶ� 
#include "Components/TextBlock.h"
#include "Components/Button.h"

//���� �ε�
//����� ���������� ���� //ū�����͵��� ���� �ʴ� ���� ��õ ������ ������  �������� �����常 ����
//�񵿱� �ε�
//����� ������ �ʴ��� ���� 

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
