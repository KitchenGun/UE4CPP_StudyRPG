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

#include "Component/CPP_WidgetComponent.h"
//#include "CPP_Sword.h"


ACPlayer::ACPlayer()
{
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	CHelpers::CreateActorComponent<UCPP_StatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCPP_StateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCPP_WeaponComponent>(this,&Weapon,"Weapon");

	CHelpers::CreateActorComponent<UCPP_WidgetComponent>(this,&Widget,"Widget");
	


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

	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = false;
	
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
	PlayerInputComponent->BindAction("Wizard", IE_Pressed, this, &ACPlayer::OnWizard);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ACPlayer::OnAction);
	
	PlayerInputComponent->BindAction("SubAction",IE_Pressed,this,&ACPlayer::OnSubAction_Pressed);
	PlayerInputComponent->BindAction("SubAction",IE_Released,this,&ACPlayer::OnSubAction_Released);
	
	PlayerInputComponent->BindAction("Status",IE_Pressed,Widget,&UCPP_WidgetComponent::ToggleStatus);
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Status->SubHealth(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ACPlayer::OnMoveForward(float InAxis)
{
	//if(p == false) return; 와 같은 의미
	CheckFalse(Status->CanMove());
	CheckFalse(State->IsIdleMode());
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Status->CanMove());
	CheckFalse(State->IsIdleMode());
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	CheckTrue(Status->GetFixedCamera());//카메라 애니메이션 중간에서 회전 안하도록함
	AddControllerYawInput(InAxis * HorizontalLook * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	CheckTrue(Status->GetFixedCamera());
	AddControllerPitchInput(InAxis * VerticalLook * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnOneHand()
{
	//Sword->Equip();
	CheckFalse(State->IsIdleMode());

	Weapon->SetOneHandMode();
}

void ACPlayer::OnWizard()
{
	CheckFalse(State->IsIdleMode());
	Weapon->SetWizardMode();
}

void ACPlayer::OnAction()
{
	//Sword->Action();
	Weapon->DoAction();
}

void ACPlayer::OnSubAction_Pressed()
{
	Weapon->SubAction_Pressed();
}

void ACPlayer::OnSubAction_Released()
{
	Weapon->SubAction_Released();
}
