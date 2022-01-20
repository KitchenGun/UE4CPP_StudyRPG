#include "Component/CPP_MontageComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCPP_MontageComponent::UCPP_MontageComponent()
{
}


void UCPP_MontageComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	TArray<FMontageData*> datas;

	DataTable->GetAllRows<FMontageData>("",datas);
	for (int32 i = 0; i < (int32)EStateType::MAX; i++)
	{
		for (FMontageData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;
			}
		}
	}
}

void UCPP_MontageComponent::PlayHittedMode()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UCPP_MontageComponent::PlayDeadMode()
{
	PlayAnimMontage(EStateType::Dead);
}

void UCPP_MontageComponent::PlayAnimMontage(EStateType InType)
{
	CheckNull(OwnerCharacter);
	const FMontageData* data = Datas[(int32)InType];

	if (data && data->Montage)
	{
		OwnerCharacter->PlayAnimMontage(data->Montage,data->PlayRatio,data->SectionName);
	}
}
