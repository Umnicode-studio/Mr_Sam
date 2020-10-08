// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameObject.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MR_SAM_API UGameObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGameObject();

	// Properties:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString Label = "undefined";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	bool IsInteractive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	bool IsPickupAble = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Physics")
	int Damage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Physics")
    int Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Physics")
    bool IsBurn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Physics")
    bool IsExplode = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties|Interaction")
    bool IsInteract = false;
	
protected:
	
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
