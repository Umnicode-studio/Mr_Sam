//
// Created by anton on 8/23/2020.
//

#include "MapRoomArray.h"

bool UMapRoomArray::FixBrokenLinks(const bool Remove)
{
    if (Remove || this->Content.GetAllocatedSize() > this->LastCapacity){
        this->GlobalPositionRefsBook.Empty();
        this->CoordinatesRefsBook.Empty();

        for (int c = 0; c < this->Content.Num(); ++c){
            if (IsValid(this->Content[c]))
            {
                this->GlobalPositionRefsBook.Add(&this->Content[c]->GlobalPosition, c);
                this->CoordinatesRefsBook.Add(&this->Content[c]->Coordinates, c);
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
        this->GlobalPositionRefsBook.Add(&Room->GlobalPosition, this->Content.Num() - 1);
        this->CoordinatesRefsBook.Add(&Room->Coordinates, this->Content.Num() - 1);
    }
}

UMapRoomArray::UMapRoomArray()
{
    
}

// API:
bool UMapRoomArray::AddRoom(TSubclassOf<UMapRoom> RoomClass)
{
    if (!IsValid(RoomClass)) return false;
    
    this->LinkRoom(RoomClass.GetDefaultObject());
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
bool UMapRoomArray::RemoveRoomByGlobalPosition(int GlobalPosition)
{
    int *Index = this->GlobalPositionRefsBook.Find(&GlobalPosition);
    if (Index)
    {
        this->CoordinatesRefsBook.Remove(&this->Content[*Index]->Coordinates);
        this->Content.RemoveAt(*Index);
            
        this->GlobalPositionRefsBook.Remove(&GlobalPosition);
            
        this->FixBrokenLinks(true);
        return true;
    }

    return false;
}
bool UMapRoomArray::RemoveRoomByCoordinates(FIntPoint Coordinates)
{
    int *Index = this->CoordinatesRefsBook.Find(&Coordinates);

    if (Index){
        this->GlobalPositionRefsBook.Remove(&this->Content[*Index]->GlobalPosition);
        this->Content.RemoveAt(*Index);

        this->CoordinatesRefsBook.Remove(&Coordinates);

        this->FixBrokenLinks(true);
        return true;
    }

    return false;
}

// ---
int UMapRoomArray::GetSize() const
{
    return this->Content.Num();
}
bool UMapRoomArray::Empty() const
{
    return this->GetSize() == 0;
}

// ---
UMapRoom *UMapRoomArray::GetRoomByIndex(int Index)
{
    if (Index > -1 && Index < this->GetSize()){
        return this->Content[Index];
    }

    return nullptr; 
}
UMapRoom *UMapRoomArray::GetRoomByGlobalPosition(int GlobalPosition)
{
    int *Index = this->GlobalPositionRefsBook.Find(&GlobalPosition);

    if (Index){
        return this->Content[*Index];
    }

    return nullptr;
}
UMapRoom *UMapRoomArray::GetRoomByCoords(FIntPoint Coordinates)
{
    int *Index = this->CoordinatesRefsBook.Find(&Coordinates);

    if (Index){
        return this->Content[*Index];
    }

    return nullptr;
}
TArray<UMapRoom*> UMapRoomArray::GetRoomsOnFloor(int Floor)
{
    TArray<UMapRoom *> Rooms;

    for (int x = 0; ; x++){
        UMapRoom *Temp = this->GetRoomByCoords({x, Floor});
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