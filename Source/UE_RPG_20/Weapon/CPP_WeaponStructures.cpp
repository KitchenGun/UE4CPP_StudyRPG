#include "CPP_WeaponStructures.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/CPP_StatusComponent.h"
#include "Component/CPP_StateComponent.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundCue.h"

UCPP_WeaponStructures::UCPP_WeaponStructures()
{

}

void FDoActionData::PlayMontage(ACharacter* InOwner)
{
	UCPP_StatusComponent* status = CHelpers::GetComponent<UCPP_StatusComponent>(InOwner);
	if (status)
	{
		bCanMove?status->Move():status->Stop();
	}
	InOwner->PlayAnimMontage(Montage,PlayRatio);
}

void FDoActionData::PlayEffect(UWorld* InWorld, ACharacter* InOwner)
{
	CheckNull(Effect);

	FTransform transform = EffectTransform;
	FVector ownerLocation = InOwner->GetActorLocation();
	ownerLocation+= InOwner->GetActorRotation().RotateVector(transform.GetLocation());
	transform.SetLocation(ownerLocation);

	FRotator rotation = InOwner->GetActorRotation();
	rotation += FRotator(transform.GetRotation());
	transform.SetRotation(FQuat(rotation));

	CHelpers::PlayEffect(InWorld,Effect,transform);

}

void FDoActionData::PlayEffect(USkeletalMeshComponent* InMesh, FName InSocketName)
{
	CheckNull(Effect);

	AActor* owner = InMesh->GetOwner();
	UWorld* world = owner->GetWorld();

	CHelpers::PlayEffect(world,Effect,EffectTransform,InMesh,InSocketName);

}

void FDoActionData::EndAction(ACharacter* InOwner)
{
}



void FHitData::PlayMontage(ACharacter* InOwner)
{
}

void FHitData::PlayEffect(UWorld* InWorld, ACharacter* InOwner)
{
}

void FHitData::PlayEffect(USkeletalMeshComponent* InMesh, FName InSocketName)
{
}

void FHitData::PlaySoundCue(UWorld* InWorld, const FVector& InLocation)
{
}

void FHitData::PlayHitStop(UWorld* InWorld)
{
}

void FHitData::SendDamage(ACharacter* InAttacker, AActor* InAttackerCursor, ACharacter* InOtherCharacter)
{
}
