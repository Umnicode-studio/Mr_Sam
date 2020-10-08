// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameCharacter.generated.h"

UCLASS()
class MR_SAM_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();

	// Properties:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	bool IsInInteraction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	int ZLayer = 0;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Functions:
	UFUNCTION(BlueprintImplementableEvent)
    void Action(const FString &ActionId);
};
