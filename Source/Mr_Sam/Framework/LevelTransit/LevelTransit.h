// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Core/Registry.h"

#include "LevelTransit.generated.h"

UCLASS()
class MR_SAM_API ULevelTransit : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Utils", meta=(WorldContext=WorldContextObject))
	static bool LoadLevel(UObject *WorldContextObject, FName LevelName);
};
