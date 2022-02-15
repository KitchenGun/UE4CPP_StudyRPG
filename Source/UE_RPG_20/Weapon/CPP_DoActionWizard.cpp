#include "Weapon/CPP_DoActionWizard.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"
#include "CPP_Attachment.h"
#include "CPP_Projectile.h"

UCPP_DoActionWizard::UCPP_DoActionWizard()
{
	CHelpers::GetClass<ACPP_Projectile>(&FireBallClass,"Blueprint'/Game/Weapons/BP_CProjectileFireBall.BP_CProjectileFireBall_C'");
	
}

void UCPP_DoActionWizard::BeginPlay(ACPP_Attachment* InAttachment, ACharacter* InOwner,
	const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas)
{
	Super::BeginPlay(InAttachment, InOwner, InActionDatas, InHitDatas);
	
}

void UCPP_DoActionWizard::DoAction()
{
	Super::DoAction();
	CheckFalse(ActionDatas.Num()>0);
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	ActionDatas[0].PlayMontage(OwnerCharacter);
}

void UCPP_DoActionWizard::BeginDoAction()
{
	Super::BeginDoAction();
	for(int32 i=FireBalls.Num()-1;i>=0;i--)
	{
		if(FireBalls[i]->GetAttachParentActor())
		{
			FireBalls[i]->OnProjectileHit.AddDynamic(this,&UCPP_DoActionWizard::FireBallHit);
			FireBalls[i]->OnProjectileEndPlay.AddDynamic(this,&UCPP_DoActionWizard::FireBallDestroy);

			FireBalls[i]->Shoot(FQuat(OwnerCharacter->GetActorRotation()).GetForwardVector());
		}
	}
	
}

void UCPP_DoActionWizard::EndDoAction()
{
	Super::EndDoAction();
	ActionDatas[0].EndAction(OwnerCharacter);
	CreateFireBall();
}

void UCPP_DoActionWizard::OnEquip()
{
	Super::OnEquip();
	CreateFireBall();
}

void UCPP_DoActionWizard::OnUnEquip()
{
	Super::OnUnEquip();
	for(int32 i=FireBalls.Num()-1;i>=0;i--)
	{
		if(FireBalls[i]->GetAttachParentActor())
		{
			FireBalls[i]->Destroy();
		}
	}
}

void UCPP_DoActionWizard::CreateFireBall()
{
	FTransform transform;
	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);
	ACPP_Projectile* fireBall = World->SpawnActorDeferred<ACPP_Projectile>
	(FireBallClass,transform,NULL,NULL,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	FAttachmentTransformRules rule = FAttachmentTransformRules(EAttachmentRule::KeepRelative,true);
	fireBall->AttachToComponent(OwnerCharacter->GetMesh(),rule,"Hand_FireBall_Projectile");
	FireBalls.Add(fireBall);
	UGameplayStatics::FinishSpawningActor(fireBall,transform);
}

void UCPP_DoActionWizard::FireBallHit(AActor* InCauser, ACharacter* InOtherCharacter)
{
	HitDatas[0].SendDamage(OwnerCharacter,InCauser,InOtherCharacter);
}

void UCPP_DoActionWizard::FireBallDestroy(ACPP_Projectile* InDestroyer)
{
	FireBalls.Remove(InDestroyer);
}

