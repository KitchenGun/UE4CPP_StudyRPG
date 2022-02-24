#include "Characters/CEnemy.h"
#include "Global.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Component/CPP_StatusComponent.h"
#include "Component/CPP_StateComponent.h"
#include "Component/CPP_MontageComponent.h"
#include "Weapon/CPP_WeaponComponent.h"
#include "Weapon/CPP_WeaponStructures.h"

ACEnemy::ACEnemy()
{
	CHelpers::CreateActorComponent<UCPP_StatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCPP_StateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCPP_MontageComponent>(this,&Montage,"Montage");
	CHelpers::CreateActorComponent<UCPP_WeaponComponent>(this,&Weapon,"Weapon");
	
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/BP_CAnimInstance.BP_CAnimInstance_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	//state�� �ִ�OnStateTypeChanged�� ACEnemy::OnStateTypeChanged�� ���ε��ϰڴ�.
	State->OnStateTypeChanged.AddDynamic(this,&ACEnemy::OnStateTypeChanged);

	int count =0;
	TArray<UMaterialInterface*> materials = GetMesh()->GetMaterials();

	for (UMaterialInterface* material : materials)
	{
		UMaterialInstanceDynamic* dynamic = UMaterialInstanceDynamic::Create(material,this);
		GetMesh()->SetMaterial(count,dynamic);
		Materials.Add(dynamic);
		count++;
	}
	Change_Character_Color(OriginColor);
}

void ACEnemy::OnStateTypeChanged(EStateType InType)
{
	switch (InType)
	{
	case EStateType::Idle:
		break;
	case EStateType::Equip:
		break;
	case EStateType::Hitted:
		Hitted();
		break;
	case EStateType::Dead:
		Dead();
		break;
	case EStateType::Action:
		break;
	case EStateType::MAX:
		break;
	default:
		break;
	}
}

void ACEnemy::Change_Character_Color(FLinearColor InColor)
{
	for (UMaterialInstanceDynamic* material : Materials)
	{
		material->SetVectorParameterValue("BodyColor",InColor);
	}
}

void ACEnemy::Hitted()
{
	//Montage->PlayHittedMode();
	Change_Character_Color(FLinearColor::Red);
	FTimerHandle timerHandle;

	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()
	{
		Change_Character_Color(OriginColor);
	});
	GetWorld()->GetTimerManager().SetTimer(timerHandle,timerDelegate,0.2f,false);//���ʵڿ� timerDelegate �Լ��� ������ ���ΰ��� �����ϴ� �� �ڿ� �Ű������� �߰��� ���ϸ� a+0.2f�ڿ� �����ϴ°��� �� 

	Status->SubHealth(Damaged.DamageAmount);
	Damaged.DamageAmount=0.0f;

	if (Status->GetHP() < 0.0f)
	{
		State->SetDeadMode();
		return;
	}
	FVector start = GetActorLocation();
	FVector target = Damaged.EventInstigator->GetPawn()->GetActorLocation();



	if (Damaged.DamageEvent && Damaged.DamageEvent->HitData)
	{
		FHitData* data = Damaged.DamageEvent->HitData;
		data->PlayMontage(this);

		FTransform transform;
		transform.SetLocation(GetActorLocation());

		data->PlayEffect(GetWorld(),transform);
		data->PlayHitStop(GetWorld());
		data->PlaySoundCue((GetWorld()),GetActorLocation());

		FVector direction = target - start;
		direction.Normalize();
		LaunchCharacter(-direction*300,true,false);
	}
	Damaged.DamageEvent = NULL;
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start,target));
	Damaged.EventInstigator =NULL;
}

void ACEnemy::Dead()
{

}

float ACEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	Damaged.DamageAmount = DamageAmount;
	Damaged.EventInstigator = EventInstigator;
	Damaged.DamageEvent = (FActionDamageEvent*)&DamageEvent;
	State->SetHittedMode();
	return DamageAmount;
}
