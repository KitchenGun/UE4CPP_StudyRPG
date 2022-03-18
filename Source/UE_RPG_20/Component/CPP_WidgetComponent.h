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

	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_UserWidget_Controller* Widget_Controller;
	UPROPERTY(VisibleDefaultsOnly)
	class UCPP_UserWidget_Player* Widget_Player;
public:	
	UCPP_WidgetComponent();

	
protected:
	virtual void BeginPlay() override;

	
};
