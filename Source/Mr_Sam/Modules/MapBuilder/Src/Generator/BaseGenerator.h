//
// Created by anton on 8/21/2020.
//

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "../IO/MapInput.h"
#include "../IO/MapOutput.h"

#include "BaseGenerator.generated.h"

UCLASS(Blueprintable, Abstract)
class MR_SAM_API UBaseGenerator : public UActorComponent{
    GENERATED_BODY()
public:
    UBaseGenerator();

    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|Generator",
        meta = (WorldContext = WorldContextObject))
    virtual UMapOutput *Generate(UObject *WorldContextObject,
                                           TSubclassOf<UMapInput> InputClass);
    
protected:
    // ---
    virtual bool Init(UMapOutput *Output);
    virtual void CleanUp(UMapOutput *Output);

    // ---
    virtual void GenerateRooms(UMapOutput *Output);
    virtual void GeneratePasses(UMapOutput *Output);
    virtual void SetRoomFlags(UMapOutput *Output);
    virtual void PlaceStructures(UMapOutput *Output);

    // ---
    virtual void BeginPlay() override;
    
public:	
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                                FActorComponentTickFunction* ThisTickFunction) override;
};