#pragma once

#include "CoreMinimal.h"
#include "NiagaraDataInterfaceExport.h"
#include "Weapon/CPP_Skill.h"
#include "NiagaraDataInterfaceExport.h"
#include "CPP_SkillThron.generated.h"

UCLASS()
class UE_RPG_20_API ACPP_SkillThron : public ACPP_Skill,public INiagaraParticleCallbackHandler
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly,Category="Mesh")
	class UStaticMesh* CollisionMesh;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
	class UNiagaraComponent* Niagara;
	UPROPERTY(EditDefaultsOnly,Category="Effect")
	class UFXSystemAsset* Effect;
	
public:
	ACPP_SkillThron();
	void ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem) override;
protected:
	virtual  void BeginPlay() override;
};
