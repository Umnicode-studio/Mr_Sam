#pragma once

#include "Engine/EngineTypes.h"

template<typename ValueType>
struct TMapKeyFuncIntP : TDefaultMapKeyFuncs<int *, ValueType, false>
{
    static FORCEINLINE bool Matches(const int *A, const int *B)
    {
        return *A == *B; // match keys
    }
 
    static FORCEINLINE uint32 GetKeyHash(const int *Key)
    {
        return GetTypeHash(Key);
    }
};

template<typename ValueType>
struct TMapKeyFuncIntPointP : TDefaultMapKeyFuncs<FIntPoint *, ValueType, false>
{
    static FORCEINLINE bool Matches(const FIntPoint *A, const FIntPoint *B)
    {
        return *A == *B; // match keys
    }
 
    static FORCEINLINE uint32 GetKeyHash(const FIntPoint *Key)
    {
        return GetTypeHash(Key);
    }
};

template<typename ValueType>
struct TMultiMapKeyFuncIntPointP : TDefaultMapKeyFuncs<FIntPoint *, ValueType, true>
{
    static FORCEINLINE bool Matches(const FIntPoint *A, const FIntPoint *B)
    {
        return *A == *B; // match keys
    }
 
    static FORCEINLINE uint32 GetKeyHash(const FIntPoint *Key)
    {
        return GetTypeHash(Key);
    }
};