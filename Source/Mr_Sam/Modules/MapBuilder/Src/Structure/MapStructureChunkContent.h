// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "../Item/MapItem.h"
#include "../Utils/Structures/Sides.h"

#include "MapStructureChunkContent.generated.h"

USTRUCT(BlueprintType)
struct MR_SAM_API FMapStructureChunkContent
{
    GENERATED_BODY()

    // Properties:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<TSubclassOf<UMapItem>> Items;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<FSides> SidesConfig;

    FMapStructureChunkContent()
    {
    }

    FMapStructureChunkContent(const TArray<TSubclassOf<UMapItem>> Items,
                              const TArray<FSides> SidesConfig)
    {
        this->Items = Items;
        this->SidesConfig = SidesConfig;
    }
};