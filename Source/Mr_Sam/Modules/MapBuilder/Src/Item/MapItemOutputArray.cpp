//
// Created by anton on 8/25/2020.
//

#include "MapItemOutputArray.h"
#include "../Generator/Functions.h"

bool UMapItemOutputArray::FixBrokenLinks(bool Remove)
{
    if (Remove || this->Content.GetAllocatedSize() > this->LastCapacity){
        this->PositionRefsBook.Empty();

        for (int c = 0; c < this->Content.Num(); ++c){
            this->PositionRefsBook.Add(&this->Content[c]->Position, c);
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
        this->PositionRefsBook.Add(&Item->Position);
    }
}

UMapItemOutputArray::UMapItemOutputArray()
{
    
}

// API:
bool UMapItemOutputArray::AddItem(TSubclassOf<UMapItemOutput> ItemClass)
{
    if (!IsValid(ItemClass)) return false;
    
    this->LinkItem(ItemClass.GetDefaultObject());
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
bool UMapItemOutputArray::RemoveItem(FIntPoint Position, UMapLayer* Layer)
{
    TArray<int> ItemsIndexes;
    this->PositionRefsBook.MultiFind(&Position, ItemsIndexes);

    // Try to find item with target layer
    for (int Index : ItemsIndexes)
    {
        if (Index > 0 && Index < this->Content.Num())
        {
            if (this->Content[Index]->Layers.Find(Layer) != INDEX_NONE)
            {
                this->Content.RemoveAt(Index);
                return true;
            }
        }
    }

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

    return nullptr;
}
TArray<UMapItemOutput*> UMapItemOutputArray::GetItemsByPosition(FIntPoint Position)
{
    TArray<int> ItemsIndexes;
    TArray<UMapItemOutput *> Items;
    
    this->PositionRefsBook.MultiFind(&Position, ItemsIndexes);

    for (int Index : ItemsIndexes)
    {
        if (Index > 0 && Index < this->Content.Num())
        {
            Items.Add(this->Content[Index]);
        }
    }
    
    return Items;
}

// ---
UMapItemOutput *UMapItemOutputArray::FindItem(FIntPoint Position, UMapLayer* Layer)
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
UMapItemOutput* UMapItemOutputArray::FindItemThatPossesPoint(FIntPoint Point, UMapLayer* Layer)
{
    // Try to optimize find process
    UMapItemOutput *Item = this->FindItem(Point, Layer);

    if (!IsValid(Item)){
        for (UMapItemOutput *SItem : this->Content){ // Check is bound
            if (UGeneratorUtils::IsBound(Point, SItem->Position,
                SItem->Position + SItem->Size))
            {
                return SItem;
            }
        }

        return nullptr;
    }

    return Item;
}

// ---
TArray<UMapItemOutput *> &UMapItemOutputArray::GetContent()
{
    return this->Content;
}
