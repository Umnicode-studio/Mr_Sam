// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"
#include "Weapon.generated.h"

UENUM()
enum EWeaponShootMode
{
	Off       UMETA(DisplayName="Off"),
	Automatic UMETA(DisplayName="Automatic"),
	Manual    UMETA(DisplayName="Manual")
};

UCLASS()
class MR_SAM_API AWeapon : public AActor
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Properties")
	UStaticMeshComponent *WeaponComponent = nullptr;

	virtual void Fire();
};
