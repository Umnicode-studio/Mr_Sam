//
// Created by anton on 5/31/20.
//

#pragma once

#include "CoreMinimal.h"

#include "MapStructureChunk.h"

#include "MapStructure.generated.h"

UCLASS(Blueprintable)
class MR_SAM_API UMapStructure : public UMapObject
{
    GENERATED_BODY()
public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString Id = "None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int GlobalPosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray <FMapStructureChunk> Chunks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray <FString> ProtectedBy;

    UMapStructure();

    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapStructure")
    int GetStructureWidth() const;

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapStructure",
              meta = (WorldContext = WorldContextObject))
    static UMapStructure *MAKE(UObject *WorldContextObject, const FString StructureId,
                               const int StructureGlobalPosition,
                               const TArray<FMapStructureChunk> StructureChunks,
                               const TArray<FString> StructureProtectedBy);
};