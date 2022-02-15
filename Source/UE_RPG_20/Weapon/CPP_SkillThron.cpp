#include "Weapon/CPP_SkillThron.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"


ACPP_SkillThron::ACPP_SkillThron()
{
	CHelpers::CreateComponent<USceneComponent>(this,&Root,"Root");
	CHelpers::CreateComponent<UNiagaraComponent>(this,&Niagara,"Niagara",Root);
	
	
}

void ACPP_SkillThron::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data,
	UNiagaraSystem* NiagaraSystem)
{
	INiagaraParticleCallbackHandler::ReceiveParticleData_Implementation(Data, NiagaraSystem);
	if(!Data[0].Position.IsNearlyZero())
	{
		FVector location = Data[0].Velocity;
		FTransform transform;
		transform.SetLocation(location);
	
		CHelpers::PlayEffect(GetWorld(),Effect,transform);
		if(CollisionMesh)
		{
			FBox box = CollisionMesh->GetBoundingBox();
			FVector center = box.GetCenter();
			FVector extent = box.GetExtent();

			TArray<FHitResult> hitResult;
			TArray<TEnumAsByte<EObjectTypeQuery>> objects;
			objects.Add(EObjectTypeQuery::ObjectTypeQuery3);

			TArray<AActor*> ignore;
			ignore.Add(OwnerCharacter);
			UKismetSystemLibrary::BoxTraceMultiForObjects
			(GetWorld(),location,location,extent,FRotator::ZeroRotator,objects,false,
				ignore,EDrawDebugTrace::ForDuration,hitResult,true);
		}
	}
}

void ACPP_SkillThron::BeginPlay()
{
	Super::BeginPlay();
	Niagara->SetNiagaraVariableObject("Collision",this);
}
