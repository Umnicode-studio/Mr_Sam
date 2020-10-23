//
// Created by anton on 6/6/20.
//

#pragma once

#include "CoreMinimal.h"

#include "Engine/StaticMeshActor.h"

#include "../Utils/Constants.h"
#include "../Layer/MapLayer.h"

#include "MapItem.generated.h"

class UMapOutput;

UENUM()
enum EItemLocation {
    L_Any     UMETA(DisplayName="Any"),
    L_Top     UMETA(DisplayName="Top"),
    L_Down    UMETA(DisplayName="Down"),
    L_Left    UMETA(DisplayName="Left"),
    L_Right   UMETA(DisplayName="Right")
};

UCLASS(Blueprintable)
class MR_SAM_API UMapItem : public UMapObject {
    GENERATED_BODY()
public:
    UMapItem();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
    TSubclassOf<AActor> ActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString Id = "None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TEnumAsByte<EItemLocation> Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FIntPoint Size = {1, 1};
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<TSubclassOf<UMapLayer>> Layers;

    // Additional variable that show us does this item is tile.
    // Only works with change in editor
    UPROPERTY(VisibleAnywhere, Category="Properties")
    bool IsMapTile = false;

    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItem",
        meta = (WorldContext = WorldContextObject))
    bool Place(UObject *WorldContextObject, FIntPoint NewPosition, UMapOutput *Output) const;

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItem",
        meta = (WorldContext = WorldContextObject))
    static bool CreateAndPlace(UObject *WorldContextObject, TSubclassOf<UMapItem> ItemClass,
        FIntPoint ItemPosition, UMapOutput *Output);
    
    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItem",
        meta = (WorldContext = WorldContextObject))
    static UMapItem *MAKE(UObject *WorldContextObject, TSubclassOf<AActor> ItemActorClass,
                          const FString ItemId,
                          const TEnumAsByte<EItemLocation> ItemLocation,
                          const FIntPoint ItemSize, TArray<TSubclassOf<UMapLayer>> ItemLayers);
    
    // ---
    virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
};
