// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilsFunctions.h"

// API:
bool UUtilsFunctions::IsItemMapTile(AActor *ItemActor) 
{
    return IsValid(dynamic_cast<AStaticMeshActor *> (ItemActor));
}
