#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CPP_LevelScriptTitle.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_LevelScriptTitle : public ALevelScriptActor
{
	GENERATED_BODY()
private:
	TSubclassOf<class UCPP_UserWidget_Title> BP_CPPWidget_Title;
public:
	ACPP_LevelScriptTitle();
protected:
	virtual void BeginPlay() override;
	
};
