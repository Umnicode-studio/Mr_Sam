//
// Created by anton on 8/23/2020.
//

#include "MapRoomArray.h"

bool UMapRoomArray::FixBrokenLinks(const bool Remove)
{
    if (Remove || this->Content.GetAllocatedSize() > this->LastCapacity){
        this->GlobalPositionRefsBook.clear();
        this->CoordinatesRefsBook.clear();

        for (int32 c = 0; c < this->Content.Num(); ++c){
            if (IsValid(this->Content[c]))
            {
                this->GlobalPositionRefsBook.emplace(&this->Content[c]->GlobalPosition, c);
                this->CoordinatesRefsBook.emplace(&this->Content[c]->Coordinates, c);
            }
        }

        this->LastCapacity = this->Content.GetAllocatedSize();
        return true; 
    }

    return false;  
}
void UMapRoomArray::LinkRoom(UMapRoom *Room)
{
    this->Content.Add(Room);

    if (!this->FixBrokenLinks())
    {
        this->GlobalPositionRefsBook.emplace(&Room->GlobalPosition, this->Content.Num() - 1);
        this->CoordinatesRefsBook.emplace(&Room->Coordinates, this->Content.Num() - 1);
    }
}

UMapRoomArray::UMapRoomArray()
{
    
}

// API:
bool UMapRoomArray::AddRoom(UObject *WorldContextObject, TSubclassOf<UMapRoom> RoomClass)
{
    if (!IsValid(RoomClass) || !IsValid(WorldContextObject)) return false;
    
    this->LinkRoom(DuplicateObject(RoomClass.GetDefaultObject(), WorldContextObject));
    return true;
}
bool UMapRoomArray::AddExistRoom(UMapRoom *Room)
{
    if (IsValid(Room))
    {
        this->LinkRoom(Room);   
        return true;
    }

    return false;
}

// --
bool UMapRoomArray::RemoveRoomByGlobalPosition(int32 GlobalPosition)
{
    const auto Iterator = this->GlobalPositionRefsBook.find(&GlobalPosition);
    if (Iterator != this->GlobalPositionRefsBook.end())
    {
        this->CoordinatesRefsBook.erase(this->CoordinatesRefsBook.find(
                                           &this->Content[Iterator->second]->Coordinates));
        
        this->Content.RemoveAt(Iterator->second);
            
        this->GlobalPositionRefsBook.erase(Iterator);
            
        this->FixBrokenLinks(true);
        return true;
    }

    return false;
}
bool UMapRoomArray::RemoveRoomByCoordinates(FRoomCoordinates Coordinates)
{
    const auto Iterator = this->CoordinatesRefsBook.find(&Coordinates);

    if (Iterator != this->CoordinatesRefsBook.end()){
        this->GlobalPositionRefsBook.erase(this->GlobalPositionRefsBook.find(
                                                      &this->Content[Iterator->second]->GlobalPosition));
        
        this->Content.RemoveAt(Iterator->second);
        this->CoordinatesRefsBook.erase(Iterator);

        this->FixBrokenLinks(true);
        return true;
    }

    return false;
}
bool UMapRoomArray::RemoveItemByIndex(int32 Index)
{
    if (Index > 0 && Index < this->Content.Num())
    {
        this->Content.RemoveAt(Index);
    }
    return false;
}

// ---
int32 UMapRoomArray::Num() const
{
    return this->Content.Num();
}
bool UMapRoomArray::Empty() const
{
    return this->Num() == 0;
}

// ---
UMapRoom *UMapRoomArray::GetRoomByIndex(int32 Index)
{
    if (Index > -1 && Index < this->Num()){
        return this->Content[Index];
    }

    return nullptr; 
}
UMapRoom *UMapRoomArray::GetRoomByGlobalPosition(int32 GlobalPosition)
{
    const auto Iterator = this->GlobalPositionRefsBook.find(&GlobalPosition);

    if (Iterator != this->GlobalPositionRefsBook.end()){
        return this->Content[Iterator->second];
    }

    return nullptr;
}
UMapRoom *UMapRoomArray::GetRoomByCoordinates(FRoomCoordinates Coordinates)
{
    const auto Iterator = this->CoordinatesRefsBook.find(&Coordinates);

    if (Iterator != this->CoordinatesRefsBook.end()){
        return this->Content[Iterator->second];
    }

    return nullptr;
}
TArray<UMapRoom*> UMapRoomArray::GetRoomsOnFloor(int32 Floor)
{
    TArray<UMapRoom *> Rooms;

    for (int32 x = 0; ; x++){
        UMapRoom *Temp = this->GetRoomByCoordinates({x, Floor});
        if (!Temp) break; // If we get the last room on the floor

        Rooms.Add(Temp);
    }
    
    return Rooms;
}

// ---
TArray<UMapRoom*> &UMapRoomArray::GetContent()
{
    return this->Content;
}