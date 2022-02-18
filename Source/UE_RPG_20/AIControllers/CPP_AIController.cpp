#include "AIControllers/CPP_AIController.h"
#include "Global.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACPP_AIController::ACPP_AIController()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(L"Perception"));
	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(L"Sight");

	SightSense->SightRadius = 90;
}
