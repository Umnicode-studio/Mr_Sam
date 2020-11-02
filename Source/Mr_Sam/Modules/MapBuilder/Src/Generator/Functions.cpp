//
// Created by anton on 8/21/2020.
//
#include "Functions.h"

// API:
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
        if (Temp && Temp->Coordinates.Floor == Room->Coordinates.Floor){
            Neighbors.Add(MAKE_FRoomNeighbor(S_Left, Temp));
        }

        // Right
        Temp = Output->Rooms->GetRoomByGlobalPosition(Room->GlobalPosition + 1);
        if (Temp && Temp->Coordinates.Floor == Room->Coordinates.Floor){
            Neighbors.Add(MAKE_FRoomNeighbor(S_Right, Temp));
        }

        // Up
        TArray<UMapRoom *> RoomsOnFloor = Output->Rooms->GetRoomsOnFloor(
                                                             Room->Coordinates.Floor - 1);
        for (UMapRoom *NRoom : RoomsOnFloor){
            if (IsValid(NRoom)) {
                if (Room->Start.X <= NRoom->Finish.X && Room->Finish.X >= NRoom->Start.X){
                    Neighbors.Add(MAKE_FRoomNeighbor(S_Up, NRoom));
                }
            }
        }

        // Down
        RoomsOnFloor = Output->Rooms->GetRoomsOnFloor(Room->Coordinates.Floor + 1);
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
bool UGeneratorUtils::IsStepsHere(const FString StepsId, const FIntPoint &Position, UMapOutput* Output)
{
    if (IsValid(Output) && IsValid(Output->Items))
    {
        return Output->Items->FindItemsThatPossesPointById(Position, StepsId).Num() != 0;
    }

    return false;
}
bool UGeneratorUtils::IsWallHere(const FString WallId, const FIntPoint &Position, UMapOutput* Output)
{
    if (IsValid(Output) && IsValid(Output->Items))
    {
        return Output->Items->FindItemsThatPossesPointById(Position, WallId).Num() != 0;
    }

    return false;
}

// ---

// ---