//
// Created by anton on 6/6/20.
//

#pragma once

#include "CoreMinimal.h"

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

UCLASS()
class MR_SAM_API UMapItemOutput : public UMapObject {
    GENERATED_BODY()
public:
    UMapItemOutput();

    // Properties:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString Id = "None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FIntPoint Position;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FIntPoint Size;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<UMapLayer *> Layers;

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutput", meta = (WorldContext = WorldContextObject))
    static UMapItemOutput *MAKE(UObject *WorldContextObject, const FString NId,
                                const FIntPoint NPosition, const FIntPoint NSize,
                                TArray<TSubclassOf<UMapLayer>> NLayers);
};

UCLASS(Blueprintable)
class MR_SAM_API UMapItemInput : public UMapObject {
    GENERATED_BODY()
public:
    UMapItemInput();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString Id = "None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TEnumAsByte<EItemLocation> Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FIntPoint Size;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<TSubclassOf<UMapLayer>> LayersUse;

    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemInput",
        meta = (WorldContext = WorldContextObject))
    bool Place(UObject *WorldContextObject, FIntPoint NewPosition, UMapOutput *Output) const;

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemInput",
        meta = (WorldContext = WorldContextObject))
    static bool CreateAndPlace(UObject *WorldContextObject, TSubclassOf<UMapItemInput> ItemClass,
        FIntPoint ItemPosition, UMapOutput *Output);

    virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
};