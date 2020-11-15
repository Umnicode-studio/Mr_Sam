// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "../Utils/Constants.h"
#include "MapStructureChunkContent.h"

#include "MapStructureChunk.generated.h"

USTRUCT(BlueprintType)
struct MR_SAM_API FMapStructureChunk
{
    GENERATED_BODY()

    // Properties:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString Id = "None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int32 Order = I_Random;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int32 Width = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<FMapStructureChunkContent> Content;

    FMapStructureChunk()
    {
        
    }

    FMapStructureChunk(const FString Id, const int32 Order, const int32 Width,
                       const TArray<FMapStructureChunkContent> Content)
    {
        this->Id = Id;
        
        this->Order = Order;
        this->Width = Width;

        this->Content = Content;
    }
};