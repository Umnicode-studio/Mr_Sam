// (c) DPACK.inc

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
};