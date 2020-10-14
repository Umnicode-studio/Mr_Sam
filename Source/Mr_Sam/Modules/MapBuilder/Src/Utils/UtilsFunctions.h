// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/StaticMeshActor.h"

#include "UtilsFunctions.generated.h"

/**
 * 
 */
UCLASS()
class MR_SAM_API UUtilsFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
    
    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|Utils")
    static bool IsItemMapTile(AActor *ItemActor);
};
