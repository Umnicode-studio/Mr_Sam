//
// Created by anton on 6/11/20.
//

#include "MapItem.h"

#include "../IO/MapOutput.h"

// Output
UMapItemOutput::UMapItemOutput()
{
    
}

UMapItemOutput* UMapItemOutput::MAKE(UObject* WorldContextObject, 
                                     const FString NId, const FIntPoint NPosition,
                                     const FIntPoint NSize, TArray<TSubclassOf<UMapLayer>> NLayers)
{
    if (IsValid(WorldContextObject))
    {
        UMapItemOutput *Item = NewObject<UMapItemOutput>(WorldContextObject);

        if (IsValid(Item))
        {
            Item->Id = NId;

            Item->Position = NPosition;
            Item->Size = NSize;

            // Link layers
            for (auto LayerClass : NLayers)
            {
                if (IsValid(LayerClass))
                {
                    Item->Layers.Add(LayerClass.GetDefaultObject());
                }
            }

            return Item;
        }
    }

    return nullptr;
}


// Input
UMapItemInput::UMapItemInput()
{
    
}

bool UMapItemInput::Place(UObject *WorldContextObject, FIntPoint NewPosition, UMapOutput *Output) const
{
    // Add item to output
    if (IsValid(Output) && IsValid(Output->Items))
    {
        Output->Items->AddExistItem(UMapItemOutput::MAKE(WorldContextObject, this->Id, NewPosition,
            this->Size, this->LayersUse));
        
        return true;
    }

    return false;
}

bool UMapItemInput::CreateAndPlace(UObject *WorldContextObject,
                                   TSubclassOf<UMapItemInput> ItemClass,
                                   FIntPoint ItemPosition,
                                   UMapOutput* Output)
{
    if (IsValid(ItemClass) && IsValid(Output))
    {
        UMapItemInput *Item = ItemClass.GetDefaultObject();
        
        Output->Items->AddExistItem(UMapItemOutput::MAKE(WorldContextObject, Item->Id, ItemPosition,
            Item->Size, Item->LayersUse));

        return true;
    }

    return false;
}


void UMapItemInput::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    TArray<TSubclassOf<UMapLayer>> UniqueLayers;
    for (int c = 0; c < this->LayersUse.Num(); c++)
    {
        if (UniqueLayers.Find(this->LayersUse[c]) == INDEX_NONE)
        {
            UniqueLayers.Add(this->LayersUse[c]);
        }
        else
        {
            this->LayersUse.RemoveAt(c);
            c--;
        }
    }
}
