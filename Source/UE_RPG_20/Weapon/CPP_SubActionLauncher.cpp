#include "Weapon/CPP_SubActionLauncher.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CPP_StateComponent.h"
#include "Components/CapsuleComponent.h"

UCPP_SubActionLauncher::UCPP_SubActionLauncher(){}

void UCPP_SubActionLauncher::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);
	OwnerRadius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
}

void UCPP_SubActionLauncher::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);
	CheckFalse(bMoving);
	FVector location = OwnerCharacter->GetActorLocation();
	if(location.Equals(End,OwnerRadius*2))
	{//한계까지 도달하면 같은 위치로 고정
		bMoving =false;
		Start = End = OwnerCharacter->GetActorLocation();
	}
	//아닐경우 End를 향해서 계속 이동
	location = UKismetMathLibrary::VInterpTo(location,End,InDeltaTime,Speed);
	
	//OwnerCharacter->GetCharacterMovement()->AddImpulse();
	//OwnerCharacter->SetActorLocation();
	
	FVector direction = (End - Start).GetSafeNormal2D();
	OwnerCharacter->AddActorWorldOffset(direction*Speed,true);
}

void UCPP_SubActionLauncher::Pressed()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(State->IsSubActionMode());
	Super::Pressed();
	State->SetActionMode();
	State->OnSubActionMode();
	ActionData.SpawnGhostTrail(OwnerCharacter);
	ActionData.PlayMontage(OwnerCharacter);
}

void UCPP_SubActionLauncher::Begin_SubAction()
{
	Super::Begin_SubAction();
	bMoving = true;
	Start = OwnerCharacter->GetActorLocation();
	End = Start+OwnerCharacter->GetActorForwardVector()*Distance;

	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);
	TArray<FHitResult> hitResults;

	float y = OwnerRadius;
	float z = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FRotator rotation = OwnerCharacter->GetActorRotation();

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery3);
	UKismetSystemLibrary::BoxTraceMultiForObjects(OwnerCharacter->GetWorld(),Start,End,FVector(0,y,z),
		rotation,objects,false,ignores,DrawDebug,hitResults,true);

	for (const FHitResult& hitResult : hitResults)
	{
		ACharacter* character = Cast<ACharacter>(hitResult.GetActor());
		if(character)
		{
			character->GetCapsuleComponent()->SetCollisionProfileName("Launcher");
			Overlapped.AddUnique(character);
		}
	}
}

void UCPP_SubActionLauncher::End_SubAction()
{
	Super::End_SubAction();
	bMoving = false;
	for (ACharacter* character : Overlapped)
	{
		character->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
	}

	State->OffSubActionMode();
	ActionData.EndAction(OwnerCharacter);
}


void UCPP_SubActionLauncher::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);

	for (ACharacter* character : Hitted)
	{
		CheckTrue(character == InOtherCharacter);
	}

	Hitted.AddUnique(InOtherCharacter);
	//수정한 부분
	if(IsValid(OwnerCharacter)&&IsValid(InAttackCauser)&&IsValid(InOtherCharacter))
		HitData.SendDamage(OwnerCharacter,InAttackCauser,InOtherCharacter);
	else
	{
		UE_LOG(LogTemp,Display,L"OwnerCharacter%d",IsValid(OwnerCharacter));
		UE_LOG(LogTemp,Display,L"InAttackCauser%d",IsValid(InAttackCauser));
		UE_LOG(LogTemp,Display,L"InOtherCharacter%d",IsValid(InOtherCharacter));//이놈이 문제인듯 ...
	}
}

void UCPP_SubActionLauncher::OffAttachmentCollision()
{
	Super::OffAttachmentCollision();
	CheckFalse(State->IsSubActionMode());
	Hitted.Empty();
}

