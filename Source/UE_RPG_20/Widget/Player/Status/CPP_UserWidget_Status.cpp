#include "Widget/Player/Status/CPP_UserWidget_Status.h"
#include "Global.h"
#include "Components/ScrollBox.h"
#include "CPP_UserWidget_PlayerStatusRow.h"
#include "Component/CPP_StatusComponent.h"
#include "Characters/CPlayer.h"

UCPP_UserWidget_Status::UCPP_UserWidget_Status(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CHelpers::GetClass<UCPP_UserWidget_PlayerStatusRow>(&StatusRow_Class,"WidgetBlueprint'/Game/Widget/Player/Status/WB_CWidget_StatusRow.WB_CWidget_StatusRow_C'");
}

void UCPP_UserWidget_Status::NativeConstruct()
{
	Super::NativeConstruct();
	TArray<FStatusRowData*> data;
	
	DT_StatusRowData->GetAllRows<FStatusRowData>("",data);

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	UCPP_StatusComponent* status =CHelpers::GetComponent<UCPP_StatusComponent>(player);
	
	
	for(uint32 i=0;i<EStatusType::Max;i++)
	{
		Rows.Add(CreateWidget<UCPP_UserWidget_PlayerStatusRow>(this,StatusRow_Class));
		(Rows[i])->InitializeRow(*(data[i]));
		ScrollBox_List->AddChild(Rows[i]);
	}
	Rows[(int32)EStatusType::HP]->OnPlusButtonEvent.AddDynamic(status,&UCPP_StatusComponent::AddMaxHealth);
	Rows[(int32)EStatusType::HP]->OnMinusButtonEvent.AddDynamic(status,&UCPP_StatusComponent::SubMaxHealth);
}
