// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include "Kismet/GameplayStatics.h"

AGameCharacter::AGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Enable run physics without contoller
	UCharacterMovementComponent *MovementComponent = this->GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->bRunPhysicsWithNoController = true;
	}
}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}