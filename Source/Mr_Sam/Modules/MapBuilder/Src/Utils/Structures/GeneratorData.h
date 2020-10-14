#pragma once

#include "CoreMinimal.h"
#include "../../Item/MapItem.h"
#include "GeneratorData.generated.h"

USTRUCT(BlueprintType)
struct MR_SAM_API FGeneratorData
{
    GENERATED_BODY()

    // Properties:
    UPROPERTY(VisibleAnywhere, Category="Properties")
    UMapLayer *DefaultLayer = nullptr;  

    // Primitive items
    UPROPERTY(VisibleAnywhere, Category="Properties")
    UMapItem *WallItem = nullptr;

    UPROPERTY(VisibleAnywhere, Category="Properties")
    UMapItem *WallWithHoleItem = nullptr;

    UPROPERTY(VisibleAnywhere, Category="Properties")
    UMapItem *StepsItem = nullptr;

    UPROPERTY(VisibleAnywhere, Category="Properties")
    UMapItem *DoorItem = nullptr;
};