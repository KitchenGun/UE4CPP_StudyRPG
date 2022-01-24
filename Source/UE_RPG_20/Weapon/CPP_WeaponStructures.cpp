#include "CPP_WeaponStructures.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/CPP_StatusComponent.h"
#include "Component/CPP_StateComponent.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundCue.h"
//전역 맴버 변수 초기화
UAnimMontage* UCPP_WeaponStructures::DefaultHitMontage = nullptr;

UCPP_WeaponStructures::UCPP_WeaponStructures()
{
	CHelpers::GetAsset<UAnimMontage>(&DefaultHitMontage,"AnimMontage'/Game/Character/Montages/Common/HitReaction_Montage.HitReaction_Montage'");
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
	UCPP_StatusComponent* status = CHelpers::GetComponent<UCPP_StatusComponent>(InOwner);
	if(status)
		status->Move();

	UCPP_StateComponent* state = CHelpers::GetComponent<UCPP_StateComponent>(InOwner);

	if(state)
		state->SetIdleMode();
}



void FHitData::PlayMontage(ACharacter* InOwner)
{
	UCPP_StatusComponent* status = CHelpers::GetComponent<UCPP_StatusComponent>(InOwner);

	if(status)
		bCanMove ? status->Move():status->Stop();

	UAnimMontage* montage = Montage? Montage:UCPP_WeaponStructures::GetDefaultHitMontage();
	if(Montage)
		InOwner->PlayAnimMontage(montage,PlayRatio);

}

void FHitData::PlayEffect(UWorld* InWorld, const FTransform& InTransform)
{
	CheckNull(Effect);

	FTransform transform = EffectTransform;
	transform.SetRotation(InTransform.GetRotation());
	transform.AddToTranslation(InTransform.GetLocation());
	
	CHelpers::PlayEffect(InWorld,Effect,transform);
}

void FHitData::PlayEffect(USkeletalMeshComponent* InMesh, FName InSocketName)
{
	CheckNull(Effect);

	AActor* owner = InMesh->GetOwner();
	UWorld* world = owner->GetWorld();

	CHelpers::PlayEffect(world, Effect, EffectTransform, InMesh, InSocketName);

}

void FHitData::PlaySoundCue(UWorld* InWorld, const FVector& InLocation)
{
	CheckNull(SoundCue);

	UGameplayStatics::SpawnSoundAtLocation(InWorld,SoundCue,InLocation);

}

void FHitData::PlayHitStop(UWorld* InWorld)
{
	CheckTrue(FMath::IsNearlyZero(StopTime));
	//맞으면 시간이 느리게 가도록 하는 함수
	UGameplayStatics::SetGlobalTimeDilation(InWorld, 0.001f);

	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()
	{
		UGameplayStatics::SetGlobalTimeDilation(InWorld,1);
	});

	FTimerHandle timerHandle;
	InWorld->GetTimerManager().SetTimer(timerHandle,timerDelegate,StopTime,false);
}

void FHitData::SendDamage(ACharacter* InAttacker, AActor* InAttackerCursor, ACharacter* InOtherCharacter)
{
	FActionDamageEvent e;
	e.HitData = this;
	InOtherCharacter->TakeDamage(Power,e,InAttacker->GetController(),InAttackerCursor);
}
