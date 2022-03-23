#pragma once

#include "CoreMinimal.h"
#include "Widget/CPP_UserWidget_Closable.h"
#include "CPP_UserWidget_Status.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_UserWidget_Status : public UCPP_UserWidget_Closable
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	class UScrollBox* ScrollBox_List;
public:
	UCPP_UserWidget_Status(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DataTable")
	class UDataTable* DT_StatusRowData;

protected:
	virtual void NativeConstruct() override;
	
private:
	TSubclassOf<class UCPP_UserWidget_PlayerStatusRow> StatusRow_Class;

	TArray<UCPP_UserWidget_PlayerStatusRow*> Rows;
};
