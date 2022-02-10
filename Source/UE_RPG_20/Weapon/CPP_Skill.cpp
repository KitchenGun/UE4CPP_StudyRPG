#include "Weapon/CPP_Skill.h"
#include "Global.h"
#include "GameFramework/Character.h"


ACPP_Skill::ACPP_Skill()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACPP_Skill::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void ACPP_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

