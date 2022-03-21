#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_UserWidget_Player.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_UserWidget_Player : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	class UCPP_UserWidget_PlayerState* Player_State;
	
protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE UCPP_UserWidget_PlayerState* GetPlayerState()
	{
		return Player_State;
	}
};
