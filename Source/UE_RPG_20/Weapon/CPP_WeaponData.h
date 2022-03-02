#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_WeaponData.generated.h"

UCLASS()
class UE_RPG_20_API UCPP_WeaponData : public UObject
{
	GENERATED_BODY()

private:
	friend class UCPP_WeaponAsset;
	
public:
	FORCEINLINE class ACPP_Attachment* GetAttachment() {return Attachment;}
	FORCEINLINE class UCPP_Equipment* GetEquipment() { return Equipment; }
	FORCEINLINE class UCPP_DoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class UCPP_SubAction* GetSubAction() {return SubAction;}

private:
	class ACPP_Attachment* Attachment;

	class UCPP_Equipment* Equipment;

	class UCPP_DoAction* DoAction;

	class UCPP_SubAction* SubAction;
};
