//
// Created by anton on 8/25/2020.
//

#include "MapItemOutputArray.h"
#include "../Utils/UtilsFunctions.h"

bool UMapItemOutputArray::FixBrokenLinks(bool Remove)
{
    if (Remove || this->Content.GetAllocatedSize() > this->LastCapacity){
        this->PositionRefsBook.clear();

        for (int c = 0; c < this->Content.Num(); ++c){
            this->PositionRefsBook.emplace(&this->Content[c]->Position, c);
        }

        this->LastCapacity = this->Content.GetAllocatedSize();
        return true;
    }

    return false;
}
void UMapItemOutputArray::LinkItem(UMapItemOutput *Item)
{
    this->Content.Add(Item);

    if (!this->FixBrokenLinks())
    {
        this->PositionRefsBook.emplace(&Item->Position, this->Content.Num() - 1);
    }
}

UMapItemOutputArray::UMapItemOutputArray()
{
    
}

// API:
bool UMapItemOutputArray::AddItem(UObject *WorldContextObject, TSubclassOf<UMapItemOutput> ItemClass)
{
    if (!IsValid(ItemClass) || !IsValid(WorldContextObject)) return false;
    
    this->LinkItem(DuplicateObject(ItemClass.GetDefaultObject(), WorldContextObject));
    return true;
}
bool UMapItemOutputArray::AddExistItem(UMapItemOutput* Item)
{
    if (IsValid(Item))
    {
        this->LinkItem(Item);
        return true;
    }

    return false;
}

// ---
bool UMapItemOutputArray::RemoveItemByPosition(FIntPoint &Position, UMapLayer* Layer)
{
    const FIteratorRange IteratorsRange = this->PositionRefsBook.equal_range(&Position);

    // Try to find item with target layer
    for (auto Iterator = IteratorsRange.first; Iterator != IteratorsRange.second; ++Iterator)
    {
        if (this->Content[Iterator->second]->Layers.Find(Layer) != INDEX_NONE)
        {
            this->Content.RemoveAt(Iterator->second);
            return true;
        }
    }

    return false;
}
bool UMapItemOutputArray::RemoveItemsById(FIntPoint& Position, const FString Id)
{
    bool IsRemoved = false;
    const FIteratorRange IteratorsRange = this->PositionRefsBook.equal_range(&Position);

    // Try to find item with target layer
    for (auto Iterator = IteratorsRange.first; Iterator != IteratorsRange.second; ++Iterator)
    {
        if (this->Content[Iterator->second]->Id == Id)
        {
            this->Content.RemoveAt(Iterator->second);
            IsRemoved = true;
        }
    }

    this->FixBrokenLinks(true);
    return IsRemoved;
}
bool UMapItemOutputArray::RemoveItemByIndex(int Index)
{
    if (Index > 0 && Index < this->Content.Num())
    {
        this->Content.RemoveAt(Index);
    }

    this->FixBrokenLinks(true);
    return false;
}

// ---
bool UMapItemOutputArray::Empty() const
{
    return this->Num() == 0;
}
int UMapItemOutputArray::Num() const
{
    return this->Content.Num();
}

// ---
UMapItemOutput *UMapItemOutputArray::GetItemByIndex(int Index)
{
    if (Index > -1 && Index < this->Num()){
        return this->Content[Index];
    }

    this->FixBrokenLinks(true);
    return nullptr;
}
TArray<UMapItemOutput*> UMapItemOutputArray::GetItemsByPosition(FIntPoint &Position)
{
    TArray<UMapItemOutput *> Items;
    const FIteratorRange IteratorsRange = this->PositionRefsBook.equal_range(&Position);
   
    for (auto Iterator = IteratorsRange.first; Iterator != IteratorsRange.second; ++Iterator) {
        Items.Add(this->Content[Iterator->second]);
    }
    
    return Items;
}
TArray<UMapItemOutput*> UMapItemOutputArray::GetItemsByPositionAndId(FIntPoint& Position, const FString& Id)
{
    TArray<UMapItemOutput *> Items = this->GetItemsByPosition(Position);

    for (int c = 0; c < Items.Num(); ++c)
    {
        if (Items[c]->Id != Id) Items.RemoveAt(c);  
    }
    
    return Items;
}

// ---
UMapItemOutput *UMapItemOutputArray::FindItem(FIntPoint &Position, UMapLayer* Layer)
{
    TArray<UMapItemOutput *> Items = this->GetItemsByPosition(Position);

    for (UMapItemOutput *Item : Items)
    {
        if (Item->Layers.Find(Layer) != INDEX_NONE)
        {
            return Item;
        }
    }
    
    return nullptr;
}
UMapItemOutput* UMapItemOutputArray::FindItemThatPossesPointByLayer(FIntPoint Point, UMapLayer* Layer)
{
    // Try to optimize find process
    UMapItemOutput *Item = this->FindItem(Point, Layer);

    if (!IsValid(Item)){
        for (UMapItemOutput *SItem : this->Content){ // Check is bound
            if (UUtilsFunctions::IsBound(Point, SItem->Position, SItem->Size) && SItem->Layers.Contains(Layer))
            {
                return SItem;
            }
        }

        return nullptr;
    }

    return Item;
}
TArray<UMapItemOutput*> UMapItemOutputArray::FindItemsThatPossesPointById(FIntPoint Point, const FString& Id)
{
    TArray<UMapItemOutput *> Items;

    for (UMapItemOutput *SItem : this->Content){ // Check is bound
        if (UUtilsFunctions::IsBound(Point, SItem->Position, SItem->Size) && SItem->Id == Id)
        {   
            Items.Add(SItem);
        }
    }
    
    return Items;
}

// ---
TArray<UMapItemOutput *> &UMapItemOutputArray::GetContent()
{
    return this->Content;
}
