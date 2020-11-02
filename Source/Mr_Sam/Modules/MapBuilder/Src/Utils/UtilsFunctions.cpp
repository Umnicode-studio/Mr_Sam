// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilsFunctions.h"

// API:
bool UUtilsFunctions::IsBound(const FIntPoint &Point, const FIntPoint &AreaPosition, const FIntPoint &AreaSize)
{   
    if (Point.X >= AreaPosition.X && Point.X <= AreaPosition.X + (AreaSize.X - 1)) { // check is bound
        if (Point.Y >= AreaPosition.Y && Point.Y <= AreaPosition.Y + (AreaSize.Y - 1)) {
            return true;
        }
    }

    return false;
}

// ---
bool UUtilsFunctions::IsItemMapTile(AActor *ItemActor) 
{
    return IsValid(dynamic_cast<AMapTile *> (ItemActor));
}
