// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "../Components/GameObject.h"

#include "Registry.generated.h"

/**
 * 
 */
UCLASS()
class MR_SAM_API URegistry : public UGameInstance
{
	GENERATED_BODY()

public:
	URegistry(const FObjectInitializer &ObjectInitializer);
	
	// API:
	TArray <const UGameObjectComponent *> GetGameObjects() const;

protected:
	UPROPERTY()
	TArray <UGameObjectComponent *> GameObjects;

	friend class UGameObjectComponent;
};
