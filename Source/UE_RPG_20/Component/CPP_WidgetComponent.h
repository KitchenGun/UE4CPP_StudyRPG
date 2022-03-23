#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_WidgetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCPP_WidgetComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_UserWidget_Controller* WidgetController;
	
	TSubclassOf<class UCPP_UserWidget_Controller> WidgetControllerClass;
	TSubclassOf<class UCPP_UserWidget_Player> WidgetPlayerStateClass;
	TSubclassOf<class UCPP_UserWidget_Status> StatusWidgetClass;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_UserWidget_Controller* Widget_Controller;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_UserWidget_Player* Widget_Player;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_UserWidget_Status* StatusWidget;
public:	
	UCPP_WidgetComponent();

	
protected:
	virtual void BeginPlay() override;

	void OpenStatus();

	void CloseStatus();
public:
	void ToggleStatus();
	
};
