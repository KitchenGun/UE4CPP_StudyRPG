#pragma once

#include "CoreMinimal.h"
#include "Weapon/CPP_Skill.h"
#include "NiagaraSystem.h"
#include "NiagaraDataInterfaceExport.h"
#include "CPP_SkillSwordSlash.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_SkillSwordSlash : public ACPP_Skill, public INiagaraParticleCallbackHandler
{
	GENERATED_BODY()
public:
	ACPP_SkillSwordSlash();
	//��ƼŬ �����͸� ��Ƽ� tick���� ȣ���ؼ� ��ȭ�� �ֱ� ���ؼ� �����ϴ� �Լ�
	void ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem) override;
private:
	UPROPERTY(EditDefaultsOnly,Category="Damage")
	float DamageInterval =0.1f;
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* Root;
protected:
	UPROPERTY(BlueprintReadOnly,VisibleDefaultsOnly)
	class UNiagaraComponent* Niagara;
	UPROPERTY(BlueprintReadOnly,VisibleDefaultsOnly)
	class UBoxComponent* Box;
protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void OnSystemFinished(class UNiagaraComponent* pSystem);
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void SendDamage();
private:
	TArray<ACharacter*> Hitted;
	FTimerHandle TimerHandle;
};
