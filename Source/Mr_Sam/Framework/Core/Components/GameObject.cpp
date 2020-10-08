// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject.h"
#include "../Registry.h"
#include "Kismet/GameplayStatics.h"

UGameObject::UGameObject()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGameObject::BeginPlay()
{
	Super::BeginPlay();

	// Add component to registry
	URegistry *Registry = dynamic_cast<URegistry *> (UGameplayStatics::GetGameInstance(this));
	if (Registry)
	{
		Registry->GameObjectsList.Add(this); // Register
	}
}
void UGameObject::BeginDestroy()
{
	Super::BeginDestroy();

	// Remove component from registry
	URegistry *Registry = dynamic_cast<URegistry *> (UGameplayStatics::GetGameInstance(this));
	if (Registry)
	{
		Registry->GameObjectsList.Remove(this); // Unregister
	} 
}

void UGameObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

