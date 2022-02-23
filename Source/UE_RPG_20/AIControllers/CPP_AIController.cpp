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

void ACPP_AIController::OnPossess(APawn* InPawn)//BeginPlay �������� �����
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
	//��� ������ ���ؼ� �����´�  ������ �����ϸ� Ư�� �������� ������ �� ��ȯ
	Perception->GetCurrentlyPerceivedActors( NULL,actors);
	ACPlayer* player = nullptr;
	for(AActor* actor:actors)
	{
		player=Cast<ACPlayer>(actor);//cast �����ϸ� null ���� ��ȯ
		if(player)
			break;
	}
	Blackboard->SetValueAsObject("Player",player);
	
}
