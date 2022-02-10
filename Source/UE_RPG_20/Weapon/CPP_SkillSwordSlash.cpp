#include "Weapon/CPP_SkillSwordSlash.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"

ACPP_SkillSwordSlash::ACPP_SkillSwordSlash()
{
	CHelpers::CreateComponent<USceneComponent>(this,&Root,"Root");
	CHelpers::CreateComponent<UNiagaraComponent>(this,&Niagara,"Niagara",Root);
	CHelpers::CreateComponent<UBoxComponent>(this,&Box,"Box",Root);

	UNiagaraSystem* niagara;
	CHelpers::GetAsset<UNiagaraSystem>(&niagara,"NiagaraSystem'/Game/Effects/P_SwordAura.P_SwordAura'");
	Niagara->SetAsset(niagara);
}

void ACPP_SkillSwordSlash::BeginPlay()
{
	Super::BeginPlay();
	Niagara->OnSystemFinished.AddDynamic(this,&ACPP_SkillSwordSlash::OnSystemFinished);
	Box->OnComponentBeginOverlap.AddDynamic(this,&ACPP_SkillSwordSlash::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this,&ACPP_SkillSwordSlash::OnComponentEndOverlap);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ACPP_SkillSwordSlash::SendDamage,DamageInterval,true);
}

void ACPP_SkillSwordSlash::OnSystemFinished(UNiagaraComponent* pSystem)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	Destroy();
}

void ACPP_SkillSwordSlash::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	ACharacter* character =Cast<ACharacter>(OtherActor);
	if(character)
		Hitted.AddUnique(character);
}

void ACPP_SkillSwordSlash::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);
	ACharacter* character =Cast<ACharacter>(OtherActor);
	if(character)
		Hitted.Remove(character);
}


void ACPP_SkillSwordSlash::SendDamage()
{
	for(int32 i = Hitted.Num()-1;i>=0;i--)
		HitData.SendDamage(OwnerCharacter,this,Hitted[i]);
	
}
