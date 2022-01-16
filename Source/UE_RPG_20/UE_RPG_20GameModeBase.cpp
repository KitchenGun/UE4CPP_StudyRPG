#include "UE_RPG_20GameModeBase.h"
#include "Global.h"

AUE_RPG_20GameModeBase::AUE_RPG_20GameModeBase()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
}