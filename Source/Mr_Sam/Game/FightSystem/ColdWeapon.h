// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "ColdWeapon.generated.h"

USTRUCT(BlueprintType)
struct MR_SAM_API FKick
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FVector InitLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FVector TargetLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    float Durability = 1.0;
};

/**
 * 
 */
UCLASS()
class MR_SAM_API AColdWeapon : public AWeapon
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    float FireRate = 1.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<FKick> AvailableKicks;

    virtual void Fire() override;
};
