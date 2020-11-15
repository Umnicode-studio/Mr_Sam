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
UMapRoom* UMapRoom::MAKE(UObject* WorldContextObject, const int32 RoomWidth,
                         const FIntPoint RoomStart, const FIntPoint RoomFinish,
                         const int32 RoomGlobalPosition, const FRoomCoordinates RoomCoordinates)
{
    if (IsValid(WorldContextObject))
    {
        UMapRoom *Room = NewObject<UMapRoom>(WorldContextObject);
        if (IsValid(Room))
        {
            Room->Width = RoomWidth;
            
            Room->Start = RoomStart;
            Room->Finish = RoomFinish;

            Room->GlobalPosition = RoomGlobalPosition;
            Room->Coordinates = RoomCoordinates;

            return Room;
        }
    }
    return nullptr;
}


// ---
#if WITH_EDITOR
void UMapRoom::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    TArray<ERoomFlags> UniqueFlags;
    for (int32 c = 0; c < this->Flags.Num(); c++)
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
#endif