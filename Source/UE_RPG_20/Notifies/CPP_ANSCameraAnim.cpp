
#include "Notifies/CPP_ANSCameraAnim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraAnim.h"
#include "Weapon/CPP_CameraAnimModifier.h"
#include "Component/CPP_StatusComponent.h"


void UCPP_ANSCameraAnim::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	
	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(character);
	APlayerController* controller = character->GetController<APlayerController>();
	CheckNull(controller);

	Modifier = Cast<UCPP_CameraAnimModifier>(controller->PlayerCameraManager->AddNewCameraModifier(UCPP_CameraAnimModifier::StaticClass()));
	Modifier->SetPlayerLocation(character->GetActorLocation());
	Modifier->SetTargetLocation(character->GetActorLocation());

	controller->PlayerCameraManager->PlayCameraAnim
	(
		//카메라 애님
		CameraAnim,
		//재생 속도
		PlayerRatio,
		//scale
		1,
		//카메라가 몇초만에 갈것인가?
		BlendInTime,
		//원래 카메라로 몇초만에 갈것인가?
		BlendOutTime
		);
	UCPP_StatusComponent* status = CHelpers::GetComponent<UCPP_StatusComponent>(character);
	status->EnableFixedCamera();
	
}

void UCPP_ANSCameraAnim::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(character);
	APlayerController* controller = character->GetController<APlayerController>();
	CheckNull(controller);

	controller->PlayerCameraManager->RemoveCameraModifier(Modifier);
	UCPP_StatusComponent* status = CHelpers::GetComponent<UCPP_StatusComponent>(character);
	status->DisableFixedCamera();
}
