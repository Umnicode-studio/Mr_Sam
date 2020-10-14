//
// Created by anton on 6/11/20.
//

#include "MapItem.h"
#include "../IO/MapOutput.h"


UMapItem::UMapItem()
{
    
}

// API:
bool UMapItem::Place(UObject *WorldContextObject, FIntPoint NewPosition,
                          UMapOutput *Output) const
{
    // Add item to output
    if (IsValid(this->ActorClass) && IsValid(Output) && IsValid(Output->Items))
    {
        // Create layers
        TArray<UMapLayer *> ItemLayers;
        for (auto &LayerClass : this->Layers)
        {
            if (IsValid(LayerClass))
            {
                ItemLayers.Add(LayerClass.GetDefaultObject());
            }
        }
        
        Output->Items->AddExistItem(UMapItemOutput::MAKE(WorldContextObject,
                                    NewObject<AActor>(WorldContextObject, this->ActorClass),
                                    this->Id, NewPosition, this->Size, ItemLayers));
        
        return true;
    }

    return false;
}

bool UMapItem::CreateAndPlace(UObject *WorldContextObject,
                                   TSubclassOf<UMapItem> ItemClass,
                                   FIntPoint ItemPosition,
                                   UMapOutput* Output)
{
    if (IsValid(ItemClass) && IsValid(Output))
    {
        UMapItem *Item = ItemClass.GetDefaultObject();
        Item->Place(WorldContextObject, ItemPosition, Output);

        return true;
    }

    return false;
}

// ---
UMapItem* UMapItem::MAKE(UObject* WorldContextObject, TSubclassOf<AActor> ItemActorClass,
                         const FString ItemId,
                         const TEnumAsByte<EItemLocation> ItemLocation,
                         const FIntPoint ItemSize,
                         TArray<TSubclassOf<UMapLayer>> ItemLayers)
{
    if (IsValid(WorldContextObject))
    {
        UMapItem *Item = NewObject<UMapItem>(WorldContextObject);

        if (IsValid(Item))
        {
            Item->ActorClass = ItemActorClass;
            Item->Id = ItemId;
            Item->Location = ItemLocation;
            Item->Size = ItemSize;
            Item->Layers = ItemLayers;

            return Item;
        }
    }
    return nullptr;
}

// ---
void UMapItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    TArray<TSubclassOf<UMapLayer>> UniqueLayers;
    for (int c = 0; c < this->Layers.Num(); c++)
    {
        if (UniqueLayers.Find(this->Layers[c]) == INDEX_NONE)
        {
            UniqueLayers.Add(this->Layers[c]);
        }
        else
        {
            this->Layers.RemoveAt(c);
            c--;
        }
    }

    if (IsValid(this->ActorClass))
    {
        this->IsMapTile = UUtilsFunctions::IsItemMapTile(this->ActorClass.GetDefaultObject());
    }
    else
    {
        this->IsMapTile = false;
    }
}