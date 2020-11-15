// (c) DPACK.inc


#include "GameObject.h"
#include "../GameInstance/Registry.h"

#include "Kismet/GameplayStatics.h"

UGameObjectComponent::UGameObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGameObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	// Add component to registry
	URegistry *Registry = dynamic_cast<URegistry *> (UGameplayStatics::GetGameInstance(this));
	if (Registry)
	{
		Registry->GameObjects.Add(this); // Register
	}
}
void UGameObjectComponent::BeginDestroy()
{
	Super::BeginDestroy();

	// Remove component from registry
	URegistry *Registry = dynamic_cast<URegistry *> (UGameplayStatics::GetGameInstance(this));
	if (Registry)
	{
		Registry->GameObjects.Remove(this); // Unregister
	} 
}

void UGameObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}