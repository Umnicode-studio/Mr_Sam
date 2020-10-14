//
// Created by anton on 8/22/2020.
//

#include "BaseGenerator.h"

UBaseGenerator::UBaseGenerator()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// API:
UMapOutput *UBaseGenerator::Generate(UObject *WorldContextObject,
                                             TSubclassOf<UMapInput> InputClass) {
    // Default generator
    UMapOutput *Output = UMapOutput::MAKE(WorldContextObject, InputClass);
    
    if (IsValid(Output))
    {
        Output->IsGeneratedSuccessfully = this->Init(Output);

        if (Output->IsGeneratedSuccessfully)
        {
            this->GenerateRooms(Output);
            this->GeneratePasses(Output);
            this->SetRoomFlags(Output);
            this->PlaceStructures(Output);

            this->CleanUp(Output);
        }else
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Error init MapOutput");
            }
        }
        return Output;
    }

    return nullptr;
}

// ---
bool UBaseGenerator::Init(UMapOutput* Output)
{
    return false;
}
void UBaseGenerator::CleanUp(UMapOutput* Output)
{
    
}

// ---
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

// ---
void UBaseGenerator::BeginPlay()
{
    Super::BeginPlay();
}

void UBaseGenerator::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

