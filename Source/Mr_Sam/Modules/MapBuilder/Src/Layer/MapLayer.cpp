#include "MapLayer.h"

UMapLayer::UMapLayer()
{
    this->Id = "None";
    this->ZOffset = 0;
}

bool UMapLayer::operator==(const UMapLayer& Right) const
{
    return Right.Id == this->Id && Right.ZOffset == this->ZOffset; 
}

// API:
UMapLayer* UMapLayer::MAKE(UObject* WorldContextObject, const FString LayerId, const float LayerZOffset)
{   
    if (IsValid(WorldContextObject))
    {
        UMapLayer *Layer = NewObject<UMapLayer>(WorldContextObject);

        if (IsValid(Layer))
        {
            Layer->Id = LayerId;
            Layer->ZOffset = LayerZOffset;

            return Layer;
        }
    }

    return nullptr;
}

