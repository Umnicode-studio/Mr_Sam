#include "MapItemOutput.h"

UMapItemOutput::UMapItemOutput()
{
    
}

// API:
UMapItemOutput* UMapItemOutput::MAKE(UObject* WorldContextObject, AActor *ItemActor, 
                                     const FString ItemId, const FIntPoint ItemPosition,
                                     const FIntPoint ItemSize, TArray<UMapLayer *> ItemLayers)
{
    if (IsValid(WorldContextObject))
    {
        UMapItemOutput *Item = NewObject<UMapItemOutput>(WorldContextObject);

        if (IsValid(Item))
        {
            Item->Actor = ItemActor;
            Item->Id = ItemId;

            Item->Position = ItemPosition;
            Item->Size = ItemSize;
            
            Item->Layers = ItemLayers;

            return Item;
        }
    }

    return nullptr;
}

// ---
bool UMapItemOutput::IsMapTile() const
{
    return UUtilsFunctions::IsItemMapTile(this->Actor);
}
