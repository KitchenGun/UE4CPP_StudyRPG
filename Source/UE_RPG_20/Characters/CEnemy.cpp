#include "Characters/CEnemy.h"
#include "Global.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Component/CPP_StatusComponent.h"
#include "Component/CPP_StateComponent.h"

ACEnemy::ACEnemy()
{
	CHelpers::CreateActorComponent<UCPP_StatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCPP_StateComponent>(this, &State, "State");

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

void ACEnemy::Change_Character_Color(FLinearColor InColor)
{
	for (UMaterialInstanceDynamic* material : Materials)
	{
		material->SetVectorParameterValue("BodyColor",InColor);
	}
}

float ACEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);

	return DamageAmount;
}
