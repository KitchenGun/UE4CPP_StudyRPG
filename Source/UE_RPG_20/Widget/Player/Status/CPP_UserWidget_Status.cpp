#include "Widget/Player/Status/CPP_UserWidget_Status.h"
#include "Global.h"
#include "Components/ScrollBox.h"
#include "CPP_UserWidget_PlayerStatusRow.h"
#include "Component/CPP_StatusComponent.h"

UCPP_UserWidget_Status::UCPP_UserWidget_Status(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CHelpers::GetClass<UCPP_UserWidget_PlayerStatusRow>(&StatusRow_Class,"WidgetBlueprint'/Game/Widget/Player/Status/WB_CWidget_StatusRow.WB_CWidget_StatusRow_C'");
}

void UCPP_UserWidget_Status::NativeConstruct()
{
	Super::NativeConstruct();
	TArray<FStatusRowData*> data;
	DT_StatusRowData->GetAllRows<FStatusRowData>("DataTable'/Game/DataTable/DT_StatusRowData.DT_StatusRowData'",data);

	for(uint32 i=0;i<EStatusType::Max;i++)
	{
		Rows[i] = CreateWidget<UCPP_UserWidget_PlayerStatusRow>(this,StatusRow_Class);
		Rows[i]->InitializeRow(*(data[i]));

		ScrollBox_List->AddChild(Rows[i]);
	}
}
