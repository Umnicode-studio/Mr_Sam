// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameObject.h"


#include "Registry.generated.h"

/**
 * 
 */
UCLASS()
class MR_SAM_API URegistry : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray <UGameObject *> GameObjectsList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	TSubclassOf<UUserWidget> LevelTransitWidgetClass;
};
