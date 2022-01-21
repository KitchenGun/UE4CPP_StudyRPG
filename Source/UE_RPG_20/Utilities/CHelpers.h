#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

class UE_RPG_20_API CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		*OutObject = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		*OutObject = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *InPath));
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		*OutClass = asset.Class;
	}

	template<typename T>
	static void CreateComponent(AActor* InActor, T** OutComponent, FName InName, USceneComponent* InParent = NULL)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*OutComponent)->SetupAttachment(InParent);

			return;
		}

		InActor->SetRootComponent(*OutComponent);
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComponent, FName InName)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
	}

	template<typename T>
	static T* FindActor(UWorld* InWorld, int32 InIndex = 0)
	{
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(InWorld, T::StaticClass(), actors);

		if (actors.Num() < 1)
			return NULL;

		return Cast<T>(actors[InIndex]);
	}

	template<typename T>
	static void FindActors(UWorld* InWorld, TArray<T*>& OutActors)
	{
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(InWorld, T::StaticClass(), actors);

		for (AActor* actor : actors)
		{
			T* obj = Cast<T>(actor);

			if (!!obj)
				OutActors.Add(obj);
		}
	}

	static FLinearColor GetRandomColor()
	{
		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f;

		return color;
	}

	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	template<typename T>
	static T* GetComponent(AActor* InActor, FString InComponentName)
	{
		TArray<T*> components;
		InActor->GetComponents<T>(components);

		for(T* component : components)
		{
			if (component->GetName() == InComponentName)
				return component;
		}

		return NULL;
	}

	static FString GetStringFromEnum(FString InTypeName, int32 InIndex)
	{
		UEnum* ptr = FindObject<UEnum>(ANY_PACKAGE, *InTypeName, true);
		return ptr->GetNameStringByIndex(InIndex);
	}


	/*
	UFXSystemAsset을 사용하여서  particle과 niagara를 만듬
	particle 단독 파티클		  ex)fireball	
	niagara 파티클끼리 결합한것 ex)fireball + trail 파티클을 향상시키는 기능
	*/
	static void PlayEffect
	(UWorld* InWorld, UFXSystemAsset* InEffect, FTransform InTransform, USkeletalMeshComponent* InMesh = NULL,FName InSocketName = NAME_None)
	{
		UParticleSystem* particle = Cast<UParticleSystem>(InEffect);
		UNiagaraSystem* niagara =Cast<UNiagaraSystem>(InEffect);

		FVector location = InTransform.GetLocation();
		FRotator rotation = FRotator(InTransform.GetRotation());
		FVector scale = InTransform.GetScale3D();

		if (InMesh)
		{
			if (particle)
			{
				UGameplayStatics::SpawnEmitterAttached(particle,InMesh,InSocketName,location,rotation,scale);
				return;
			}
			if (niagara)
			{
				//object pool 방식
				
				/*
				 10초마다 1개씩 생성한다고 가정했을때 
				 Objectpool 안에 재활용가능한 객체가 없다면 생성 재활용할수있으면 객체를 활성화
				 생성객체의 할일이 끝나면 비활성화하고 Object pool 안에 담는다.
				*/																																					//현재는 Object pool 사용하지 않는다
				UNiagaraFunctionLibrary::SpawnSystemAttached(niagara, InMesh, InSocketName, location, rotation, scale,EAttachLocation::KeepRelativeOffset,true,ENCPoolMethod::None);
				return;
			}
		}
		
		if (particle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(InWorld,particle, InTransform);
			return;
		}
		if (niagara)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(InWorld,niagara,location,rotation,scale);
			return;
		}
	}
};