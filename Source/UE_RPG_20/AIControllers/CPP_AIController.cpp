#include "AIControllers/CPP_AIController.h"
#include "Global.h"
#include "AIControllers/CPP_BehaviorTreeComponent.h"
#include "Characters/CPP_EnemyAI.h"
#include "Characters/CPlayer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"


ACPP_AIController::ACPP_AIController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this,&Perception,"Perception");
	CHelpers::CreateActorComponent<UBlackboardComponent>(this,&Blackboard,"Blackboard");

	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(L"Sight");
	
	SightSense->SightRadius = 600;
	SightSense->LoseSightRadius = 800;
	SightSense->PeripheralVisionAngleDegrees = 45;
	SightSense->SetMaxAge(2);
	SightSense->DetectionByAffiliation.bDetectEnemies = true;
	SightSense->DetectionByAffiliation.bDetectNeutrals = false;
	SightSense->DetectionByAffiliation.bDetectFriendlies = false;
	Perception->ConfigureSense(*SightSense);
	Perception->SetDominantSense(*SightSense->GetSenseImplementation());
}

void ACPP_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACPP_AIController::BeginPlay()
{
	Super::BeginPlay();
	Perception->OnPerceptionUpdated.AddDynamic(this,&ACPP_AIController::OnPerceptionUpdated);
}

void ACPP_AIController::OnPossess(APawn* InPawn)//BeginPlay 다음으로 실행됨
{
	Super::OnPossess(InPawn);
	OwnerCharacter = Cast<ACPP_EnemyAI>(InPawn);
	SetGenericTeamId(OwnerCharacter->GetTeamID());
	UseBlackboard(OwnerCharacter->GetBehaviorTree()->BlackboardAsset,Blackboard);
	
	Behavior = CHelpers::GetComponent<UCPP_BehaviorTreeComponent>(OwnerCharacter);
	Behavior->SetBlackBoard(Blackboard);
	RunBehaviorTree(OwnerCharacter->GetBehaviorTree());
}

void ACPP_AIController::OnUnPossess()
{
	Super::OnUnPossess();
	
}

void ACPP_AIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*>actors;
	//모든 감각을 통해서 가져온다  감각을 지정하면 특정 감각으로 감지한 것 반환
	Perception->GetCurrentlyPerceivedActors( NULL,actors);
	ACPlayer* player = nullptr;
	for(AActor* actor:actors)
	{
		player=Cast<ACPlayer>(actor);//cast 실패하면 null 들어가서 반환
		if(player)
			break;
	}
	Blackboard->SetValueAsObject("Player",player);
	
}
