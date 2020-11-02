// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/StaticMeshActor.h"

#include "../Room/MapRoom.h"
#include "MapTile.h"

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
    UFUNCTION(BlueprintCallable, Category="MapBuilder|Functions")
    static bool IsBound(const FIntPoint &Point, const FIntPoint &AreaPosition,
                        const FIntPoint &AreaSize);
    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|Utils")
    static bool IsItemMapTile(AActor *ItemActor);

    // --- Only c++ functions
    template <class ArrayItemType, class Function>
    static void PrintArrayToLog(const TArray<ArrayItemType> &Array, Function ItemToString,
                                int Spaces = 0, char SpacesSymbol = ' ')
    {
        for (const ArrayItemType &Item : Array)
        {
            FString SpacesStr = "";
            for (int c = 0; c < Spaces; ++c) SpacesStr += SpacesSymbol;
        
            UE_LOG(LogTemp, Warning, TEXT("%s%s"), *SpacesStr, *ItemToString(Item))
        }
    }
};