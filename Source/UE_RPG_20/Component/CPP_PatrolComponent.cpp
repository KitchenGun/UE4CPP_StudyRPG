#include "Component/CPP_PatrolComponent.h"
#include "Global.h"
#include "AIControllers/BehaviorTree/CPP_PatrolPath.h"
#include "Components/SplineComponent.h"


UCPP_PatrolComponent::UCPP_PatrolComponent()
{
}

bool UCPP_PatrolComponent::GetMoveTo(FVector& OutLocation, float& OutAcceptanceDistance)
{
	OutLocation = FVector::ZeroVector;
	OutAcceptanceDistance =0.0f;
	CheckFalseResult(IsValidPath(),false);
	
	OutLocation = Path->GetSpline()->GetLocationAtSplinePoint(NextIndex,ESplineCoordinateSpace::World);
	OutAcceptanceDistance = AcceptanceDistanse;
	
	return true;
}

void UCPP_PatrolComponent::UpdateNextIndex()
{
	int32 count  = Path->GetSpline()->GetNumberOfSplinePoints();
	if(bReverse)
	{
		if(NextIndex>0)
		{
			NextIndex--;
			return;
		}


		if(Path->GetSpline()->IsClosedLoop())
		{
			NextIndex = count -1;
			return;
		}

		NextIndex = 1;
		bReverse = false;

		return;
	}
	if(NextIndex<count-1)
	{
		NextIndex++;

		return;
	}
	if(Path->GetSpline()->IsClosedLoop())
	{
		NextIndex =0;
		
		return;
	}
	NextIndex = count-2;
	bReverse = true;
}


void UCPP_PatrolComponent::BeginPlay()
{
	Super::BeginPlay();
}


