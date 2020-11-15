// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "../Layer/MapLayer.h"
#include "../Utils/UtilsFunctions.h"

#include "MapItemOutput.generated.h"

UCLASS()
class MR_SAM_API UMapItemOutput : public UMapObject {
    GENERATED_BODY()
    public:
    UMapItemOutput();

    // Properties:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    AActor *Actor = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString Id = "None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FIntPoint Position;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FIntPoint Size;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<UMapLayer *> Layers;

    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutput",
              meta = (WorldContext = WorldContextObject))
    static UMapItemOutput *MAKE(UObject *WorldContextObject, AActor *ItemActor,
                                const FString ItemId,
                                const FIntPoint ItemPosition, const FIntPoint ItemSize,
                                TArray<UMapLayer *> ItemLayers);

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutput")
    bool IsMapTile() const;
};