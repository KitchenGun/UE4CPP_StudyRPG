#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "CPP_UserWidget_PlayerStatusRow.generated.h"

USTRUCT(BlueprintType)
struct FStatusRowData: public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)//오브젝트의 경로를 저장할수있는형태
	FSoftObjectPath StatImage;
	UPROPERTY(EditAnywhere)
	FText Stat;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatusButtonClicked);

UCLASS()
class UE_RPG_20_API UCPP_UserWidget_PlayerStatusRow : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Icon;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_StatName;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Stat;

	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Plus;

	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Minus;
protected:
	virtual void NativeConstruct() override;
public:

	void InitializeRow(FStatusRowData data);
	FORCEINLINE void SetStat(int32 stat) {Stat = stat;}
private:
	UFUNCTION()
	void OnPlusButtonClicked();
	UFUNCTION()
	void OnMinusButtonClicked();
public:
	FStatusButtonClicked OnPlusButtonEvent;
	FStatusButtonClicked OnMinusButtonEvent;

	int32 Stat=0;
};
