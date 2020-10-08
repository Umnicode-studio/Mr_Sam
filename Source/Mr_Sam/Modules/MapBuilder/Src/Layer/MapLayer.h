//
// Created by anton on 6/9/20.
//

#pragma once

#include "CoreMinimal.h"

#include "../Utils/MapObject.h"

#include "MapLayer.generated.h"

UCLASS(Abstract, Blueprintable)
class MR_SAM_API UMapLayer : public UMapObject {
    GENERATED_BODY()
    
public:
    // Properties:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString Id = "None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int ZOffset = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    bool IsDefault = false;

    UMapLayer();
      
    bool operator== (const UMapLayer &Right) const;

    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapLayer",
              meta = (WorldContext = WorldContextObject))
    static UMapLayer *MAKE(UObject *WorldContextObject, const FString Layer_Id, const int Layer_ZOffset);
};