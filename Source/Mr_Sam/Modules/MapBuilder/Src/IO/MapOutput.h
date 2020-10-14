//
// Created by anton on 6/9/20.
//

#pragma once

#include "CoreMinimal.h"

#include "MapInput.h"
#include "../Layer/MapLayer.h"

#include "../Room/MapRoomArray.h"
#include "../Item/MapItemOutputArray.h"

#include "../Utils/Structures/GeneratorData.h"

#include "MapOutput.generated.h"

UCLASS(BlueprintType)
class MR_SAM_API UMapOutput : public UMapObject {
    GENERATED_BODY()
    
public:
    UMapOutput()
    {
        
    }
    
    // Properties:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    bool IsGeneratedSuccessfully = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    UMapInput *Input = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int FloorsCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FGeneratorData GeneratorData; 
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Arrays")
    UMapItemOutputArray *Items = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Arrays")
    UMapRoomArray *Rooms = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Arrays")
    TArray<UMapLayer *> Layers;
   
    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapOutput")
    bool IsHaveLayer(UMapLayer *Layer){
        if (IsValid(Layer))
        {
            for (UMapLayer *Lay : this->Layers){
                if (!IsValid(Lay)) continue;
            
                if (Lay == Layer) return true;
            }
        }

        return false;
    }

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapOutput",
              meta = (WorldContext = WorldContextObject))
    static UMapOutput *MAKE(UObject *WorldContextObject, TSubclassOf <UMapInput> InputClass)
    {
        if (IsValid(WorldContextObject))
        {
            UMapOutput *Output = NewObject<UMapOutput>(WorldContextObject);

            if (IsValid(Output))
            {
                // Create input class
                if (IsValid(InputClass))
                {
                    Output->Input = InputClass.GetDefaultObject();

                    // Create layers
                    for (auto &LayerClass : Output->Input->Layers)
                    {
                        if (IsValid(LayerClass))
                        {
                            Output->Layers.Add(LayerClass.GetDefaultObject());
                        }
                    }
                }else
                {
                    Output->IsGeneratedSuccessfully = false;
                }
        
                Output->Rooms = NewObject<UMapRoomArray>(WorldContextObject);
                Output->Items = NewObject<UMapItemOutputArray>(WorldContextObject);

                Output->GeneratorData = FGeneratorData();
        
                return Output;
            }
        }

        return nullptr;
    }
};