// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "../Core/Globals.h"

class FFrameworkCppUtils
{
public:
    template <class ArrayItemType>
    static void ShuffleTArray(TArray<ArrayItemType> &Array)
    {
        for (int32 i = 0; i < Array.Num(); i++)
        {
            const int32 Index = FMath::RandRange(0, Array.Num() - 1);
            if (Index != i)
            {
                Array.Swap(i, Index);
            }
        }
    }

    // TODO: Add log selecting and message level feature
    template <class ArrayItemType, class Function>
    static void PrintArrayToLog(const TArray<ArrayItemType> &Array, Function ItemToString,
                                int32 Spaces = 0, char SpacesSymbol = ' ')
    {
        for (const ArrayItemType &Item : Array)
        {
            FString SpacesStr = "";
            for (int32 c = 0; c < Spaces; ++c) SpacesStr += SpacesSymbol;

            UE_LOG(LogFramework, Warning, TEXT("%s%s"), *SpacesStr, *ItemToString(Item))
        }
    }
};
