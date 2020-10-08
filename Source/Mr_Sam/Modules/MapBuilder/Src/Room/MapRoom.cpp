#include "MapRoom.h"

UMapRoom::UMapRoom()
{
    
}

// API:
void UMapRoom::AddFlag(const ERoomFlags Flag)
{
    if (!this->IsHaveFlag(Flag)) this->Flags.Add(Flag);
}
bool UMapRoom::IsHaveFlag(const ERoomFlags Flag) const
{
    return this->Flags.Find(Flag) != INDEX_NONE; // finding flag
}

// ---
void UMapRoom::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    TArray<ERoomFlags> UniqueFlags;
    for (int c = 0; c < this->Flags.Num(); c++)
    {
        if (UniqueFlags.Find(this->Flags[c]) == INDEX_NONE)
        {
            UniqueFlags.Add(this->Flags[c]);
        }
        else
        {
            this->Flags.RemoveAt(c);
            c--;
        }
    }
}