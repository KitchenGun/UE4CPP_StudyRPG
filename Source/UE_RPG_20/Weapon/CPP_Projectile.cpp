#include "Weapon/CPP_Projectile.h"

ACPP_Projectile::ACPP_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACPP_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

