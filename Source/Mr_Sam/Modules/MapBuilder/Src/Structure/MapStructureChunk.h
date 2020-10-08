//
// Created by anton on 6/6/20.
//

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
    int Order = C_Random;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int Width = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<FMapStructureChunkContent> Content;

    FMapStructureChunk()
    {
        
    }

    FMapStructureChunk(const FString Id, const int Order, const int Width,
                       const TArray<FMapStructureChunkContent> Content)
    {
        this->Id = Id;
        
        this->Order = Order;
        this->Width = Width;

        this->Content = Content;
    }
};