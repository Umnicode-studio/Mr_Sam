//
// Created by anton on 8/21/2020.
//
#include "Functions.h"

// API:
bool UGeneratorUtils::IsBound(FIntPoint Point, FIntPoint AreaPosition, FIntPoint AreaSize)
{
    if (Point.X >= AreaPosition.X && Point.X <= AreaPosition.X + (AreaSize.X - 1)) { // check is bound
        if (Point.Y >= AreaPosition.Y && Point.Y <= AreaPosition.Y + (AreaSize.Y - 1)) {
            return true;
        }
    }

    return false;
}

// ---
TArray<FRoomNeighbor> UGeneratorUtils::GetRoomNeighbors(UMapRoom *Room, UMapOutput *Output)
{
    auto MAKE_FRoomNeighbor = [](ESideEnum Side, UMapRoom *Room) -> FRoomNeighbor
    {
        FRoomNeighbor Neighbor;

        Neighbor.Side = Side;
        Neighbor.Room = Room;
        
        return Neighbor;
    };
    
    TArray<FRoomNeighbor> Neighbors;

    if (IsValid(Room) && IsValid(Output) && IsValid(Output->Rooms)){
        // Left
        UMapRoom *Temp = Output->Rooms->GetRoomByGlobalPosition(Room->GlobalPosition - 1);
        if (Temp && Temp->Coordinates.Y == Room->Coordinates.Y){
            Neighbors.Add(MAKE_FRoomNeighbor(S_Left, Temp));
        }

        // Right
        Temp = Output->Rooms->GetRoomByGlobalPosition(Room->GlobalPosition + 1);
        if (Temp && Temp->Coordinates.Y == Room->Coordinates.Y){
            Neighbors.Add(MAKE_FRoomNeighbor(S_Right, Temp));
        }

        // Up
        TArray<UMapRoom *> RoomsOnFloor = Output->Rooms->GetRoomsOnFloor(Room->Coordinates.Y - 1);
        for (UMapRoom *NRoom : RoomsOnFloor){
            if (IsValid(NRoom)) {
                if (Room->Start.X <= NRoom->Finish.X && Room->Finish.X >= NRoom->Start.X){
                    Neighbors.Add(MAKE_FRoomNeighbor(S_Up, NRoom));
                }
            }
        }

        // Down
        RoomsOnFloor = Output->Rooms->GetRoomsOnFloor(Room->Coordinates.Y + 1);
        for (UMapRoom *NRoom : RoomsOnFloor){
            if (IsValid(NRoom)) {
                if (Room->Start.X <= NRoom->Finish.X && Room->Finish.X >= NRoom->Start.X){
                    Neighbors.Add(MAKE_FRoomNeighbor(S_Down, NRoom));
                }
            }
        }
    }

    return Neighbors;
}

// ---
bool UGeneratorUtils::IsStepsHere(const FString StepsId, FIntPoint Position, UMapLayer* Layer,
                                  UMapOutput* Output)
{
    if (IsValid(Layer) && IsValid(Output) && IsValid(Output->Items))
    {
        UMapItemOutput *Item = Output->Items->FindItemThatPossesPoint(Position, Layer);

        if (IsValid(Item))
        {
            return Item->Id == StepsId;
        }
    }

    return false;
}
bool UGeneratorUtils::IsWallHere(const FString WallId, FIntPoint Position, UMapLayer* Layer,
                                 UMapOutput* Output)
{
    if (IsValid(Layer) && IsValid(Output) && IsValid(Output->Items))
    {
        UMapItemOutput *Item = Output->Items->FindItemThatPossesPoint(Position, Layer);

        if (IsValid(Item))
        {
            return Item->Id == WallId;
        }
    }

    return false;
}


// ---

// ---