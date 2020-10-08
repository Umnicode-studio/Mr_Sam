// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define _WIN32_WINNT_WIN10_RS2
#define _WIN32_WINNT_WIN10_RS1

#define _WIN32_WINNT_WIN10_TH2

#include "CoreMinimal.h"

#include "../Core/Components/GameObject.h"
#include "../Core/Components/Interaction.h"
#include "../Core/Registry.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FrameworkUtils.generated.h"

/**
 * 
 */
UCLASS()
class MR_SAM_API UFrameworkUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category="FrameworkUtils", meta=(WorldContext="WorldContextObject"))
	static void IsActorGameObject(AActor *Actor, bool &Result, UGameObject *&GameObject);

	UFUNCTION(BlueprintCallable, Category="FrameworkUtils", meta=(WorldContext="WorldContextObject"))
    static void GetClosestInteractPawn(APawn* WorldContextObject, float MinDistance, APawn *&Pawn, float &Distance, UInteraction *&PawnInteraction, 
                                       UGameObject *&PawnGameObject);

	UFUNCTION(BlueprintCallable, Category="FrameworkUtils")
	static FVector GetStaticMeshSize(UStaticMesh *Mesh);
};
