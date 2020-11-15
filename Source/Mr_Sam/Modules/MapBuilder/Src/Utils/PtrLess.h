// (c) DPACK.inc

#pragma once

#include <map>
#include "../Room/MapRoom.h"

struct FPtrLessIntPointPtr
{
    bool operator()(FIntPoint *Left, FIntPoint *Right) const {
        return (Left->Y < Right->Y) || (Left->Y == Right->Y && Left->X < Right->X);
    }
};
struct FPtrLessIntPtr
{
    bool operator()(int32 *Left, int32 *Right) const {
        return *Left < *Right;
    }
};
struct FPtrLessRoomCoordinatesPtr
{
    bool operator()(FRoomCoordinates *Left, FRoomCoordinates *Right) const {
        return (Left->Floor < Right->Floor) ||
               (Left->Floor == Right->Floor && Left->PositionOnFloor < Right->PositionOnFloor);
    }
};