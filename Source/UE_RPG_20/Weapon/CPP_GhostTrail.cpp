#include "Weapon/CPP_GhostTrail.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
ACPP_GhostTrail::ACPP_GhostTrail()
{
	CHelpers::CreateComponent<UPoseableMeshComponent>(this,&Poseable,"Poseable");
	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material,"MaterialInstanceConstant'/Game/Materials/M_GhostTrail_Inst.M_GhostTrail_Inst'");
}

void ACPP_GhostTrail::BeginPlay()
{
	Super::BeginPlay();
	Poseable->SetVisibility(true);

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Poseable->SetSkeletalMesh(OwnerCharacter->GetMesh()->SkeletalMesh);
	Poseable->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());
	
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	for(int32 i =0;i<OwnerCharacter->GetMesh()->SkeletalMesh->Materials.Num();i++)
	{
		Poseable->SetMaterial(i,DynamicMaterial);
	}
	//람다의 캡쳐 블럭
	//[=],this
	//[=]값 복사 형태로 가져옴
	//[&]참조 형태로 가져옴
	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()
	{
		if(Poseable->IsVisible() == false)
		{//안보여지고 있으면 보여지도록 변경하는 함수
			Poseable->ToggleVisibility();
		}
		float height = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		SetActorLocation(OwnerCharacter->GetActorLocation()-FVector(0,0,height));
		SetActorRotation(OwnerCharacter->GetActorRotation()+FRotator(0,-90,0));
		Poseable->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());
	});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle,timerDelegate,Interval,true,StartDelay);
}

void ACPP_GhostTrail::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

