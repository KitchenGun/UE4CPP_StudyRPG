#include "AIControllers/BehaviorTree/CPP_PatrolPath.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/TextRenderComponent.h"

ACPP_PatrolPath::ACPP_PatrolPath()
{
	CHelpers::CreateComponent<USceneComponent>(this,&Scene,"Scene");
	CHelpers::CreateComponent<USplineComponent>(this,&Spline,"Spline",Scene);
	CHelpers::CreateComponent<UTextRenderComponent>(this,&Text,"Text",Scene);

	Spline->SetRelativeLocation(FVector(0,0,30));
	Text->SetRelativeLocation(FVector(0,0,120));
	Text->SetRelativeLocation(FVector(0,180,0));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->TextRenderColor = FColor::Red;

	bRunConstructionScriptOnDrag = false;
}

void ACPP_PatrolPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Text->Text = FText::FromString(GetActorLabel());
	Spline->SetClosedLoop(bLoop);
}

void ACPP_PatrolPath::BeginPlay()
{
	Super::BeginPlay();
	Text->SetVisibility(false);
}


