#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserWidget_PlayerState.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_UserWidget_PlayerState : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Name")
	FText Name;
private:
	void SetLevel(int Level);
	UFUNCTION()
	void SetHpPercent(float percent);
	UFUNCTION()
	void SetMpPercent(float percent);
	UFUNCTION()
	void SetExpPercent(float percent);
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Level;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Name;
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ProgressBar_HP;
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ProgressBar_MP;
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ProgressBar_EXP;

};
