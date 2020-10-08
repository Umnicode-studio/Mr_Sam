//
// Created by anton on 8/22/2020.
//

#include "BaseGenerator.h"

UBaseGenerator::UBaseGenerator()
{
    PrimaryComponentTick.bCanEverTick = false;
}


UMapOutput *UBaseGenerator::Generate(UObject *WorldContextObject,
                                             TSubclassOf<UMapInput> InputClass) {
    // Default generator
    UMapOutput *Output = UMapOutput::MAKE(WorldContextObject, InputClass);

    if (!IsValid(Output)) return nullptr;

    Output->IsGeneratedSuccessfully = true;

    this->Init(Output);
    
    this->GenerateRooms(Output);
    this->GeneratePasses(Output);
    this->SetRoomFlags(Output);
    this->PlaceStructures(Output);

    this->CleanUp(Output);

    return Output;
}

void UBaseGenerator::Init(UMapOutput* Output)
{
    
}
void UBaseGenerator::CleanUp(UMapOutput* Output)
{
    
}

void UBaseGenerator::GenerateRooms(UMapOutput* Output)
{
    
}
void UBaseGenerator::GeneratePasses(UMapOutput* Output)
{
    
}
void UBaseGenerator::SetRoomFlags(UMapOutput* Output)
{
    
}
void UBaseGenerator::PlaceStructures(UMapOutput* Output)
{
    
}

void UBaseGenerator::BeginPlay()
{
    Super::BeginPlay();
}

void UBaseGenerator::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

