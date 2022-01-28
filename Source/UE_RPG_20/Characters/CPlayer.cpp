#include "CPlayer.h"
#include "Global.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Component/CPP_StatusComponent.h"
#include "Component/CPP_StateComponent.h"
#include "Weapon/CPP_WeaponComponent.h"
//#include "CPP_Sword.h"


ACPlayer::ACPlayer()
{
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	CHelpers::CreateActorComponent<UCPP_StatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCPP_StateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCPP_WeaponComponent>(this,&Weapon,"Weapon");


	bUseControllerRotationYaw = false;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/BP_CAnimInstance.BP_CAnimInstance_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);


	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	//pawn에 카메라를 붙인다
	SpringArm->bEnableCameraLag = true;
	//회전값을 720 만큼 설정할수있다
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();

	//CHelpers::GetClass<ACPP_Sword>(&SwordClass, "Blueprint'/Game/BP_Sword.BP_Sword_C'");
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	//FActorSpawnParameters params;
	//params.Owner = this;
	//Sword = GetWorld()->SpawnActor<ACPP_Sword>(SwordClass, params);
	//Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "Holster_OneHand");
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("OneHand", IE_Pressed, this, &ACPlayer::OnOneHand);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ACPlayer::OnAction);
}

void ACPlayer::OnMoveForward(float InAxis)
{
	//if(p == false) return; 와 같은 의미
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	AddControllerYawInput(InAxis * HorizontalLook * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	AddControllerPitchInput(InAxis * VerticalLook * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnOneHand()
{
	//Sword->Equip();
	CheckFalse(State->IsIdleMode());

	Weapon->SetOneHandMode();
}

void ACPlayer::OnAction()
{
	//Sword->Action();
	Weapon->DoAction();
}
