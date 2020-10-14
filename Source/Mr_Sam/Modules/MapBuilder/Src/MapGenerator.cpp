#include "MapGenerator.h"

UDefaultMapGenerator::UDefaultMapGenerator()
{
    
}

bool UDefaultMapGenerator::Init(UMapOutput *Output)
{
    Output->GeneratorData = FGeneratorData();
    if (IsValid(Output->Items) && IsValid(Output->Rooms) && IsValid(Output->Input))
    {
        // Warnings
        if (Output->Input->RoomHeight == 0)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                                 "Warning, room height is 0 in "
                                                 + Output->Input->LevelName);
        }
        
        if (IsValid(Output->Input->DefaultLayer))
        {
            Output->GeneratorData.DefaultLayer = Output->Input->DefaultLayer.GetDefaultObject();
        }
        else if (Output->Layers.Num() > 0)
        {
            Output->GeneratorData.DefaultLayer = nullptr;

            for (UMapLayer *Layer : Output->Layers)
            {
                if (IsValid(Layer))
                {
                    if (!IsValid(Output->GeneratorData.DefaultLayer)) Output->GeneratorData.DefaultLayer = Layer;
                    else if (Layer->ZOffset < Output->GeneratorData.DefaultLayer->ZOffset)
                    {
                        Output->GeneratorData.DefaultLayer = Layer;
                    }
                }
            }

            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                                 "Warning, there's no valid default layer in "
                                                 + Output->Input->LevelName);
            }
        }

        // Create primitives
        if (IsValid(Output->GeneratorData.DefaultLayer))
        {
            if (IsValid(Output->Input->WallItem))
            {
                Output->GeneratorData.WallItem = Output->Input->WallItem.GetDefaultObject();
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
                                                 "Warning there's no valid Wall item in " + Output->Input->LevelName);
            }

            if (IsValid(Output->Input->WallWithHoleItem))
            {
                Output->GeneratorData.WallWithHoleItem = Output->Input->WallWithHoleItem.GetDefaultObject();
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
                                                 "Warning there's no valid WallWithHole item in " + Output->Input->LevelName);
            }

            if (IsValid(Output->Input->StepsItem))
            {
                Output->GeneratorData.StepsItem = Output->Input->StepsItem.GetDefaultObject();
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
                                                 "Warning there's no valid Steps item in " + Output->Input->LevelName);
            }
            
            if (IsValid(Output->Input->DoorItem))
            {
                Output->GeneratorData.DoorItem = Output->Input->DoorItem.GetDefaultObject();
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
                                                 "Warning there's no valid Door item in " + Output->Input->LevelName);
            }

            return IsValid(Output->GeneratorData.WallItem) && IsValid(Output->GeneratorData.WallWithHoleItem) &&
                   IsValid(Output->GeneratorData.StepsItem) && IsValid(Output->GeneratorData.DoorItem);
        
        }
    }

    return false;
}
void UDefaultMapGenerator::CleanUp(UMapOutput *Output)
{
    
}

void UDefaultMapGenerator::GenerateRooms(UMapOutput *Output)
{
    auto GetRoomArea = [](const FIntPoint StartPos, const int Length, const int Height){
        return TPair<FIntPoint, FIntPoint> (FIntPoint(StartPos.X, StartPos.Y),
               FIntPoint(StartPos.X + Length - 1, StartPos.Y + Height - 1));
    };
    
    TArray <TPair <FIntPoint, FIntPoint>> RoomArea;

    int GlobalIndex = 0;
    int FloorNumber = 0;

    int y = 1;
    while(y < Output->Input->Size.Y){ // generate floor
        // create Rooms
        int x = Output->Input->BorderSize;
        TArray <TPair <int, int>> Rooms;

        int FreeCells = Output->Input->Size.X - Output->Input->BorderSize - x;
        while (FreeCells >= Output->Input->MinRoomWidth){ // place Rooms
            int RoomSize;
            
            if (FreeCells > Output->Input->MinRoomWidth){ // prevent using int distribution with zero range
                // select random size
                int MaxLength = Output->Input->Size.X - 1 - x;
                if (Output->Input->MaxRoomWidth >= Output->Input->MinRoomWidth) MaxLength = Output->Input->MaxRoomWidth; // set max Room width
                
                RoomSize = FMath::RandRange(Output->Input->MinRoomWidth, MaxLength);
            }
            else{
                RoomSize = Output->Input->MinRoomWidth;
            }

            if (FreeCells - RoomSize - 1 < Output->Input->MinRoomWidth) { // prevent creating Rooms that smaller that MinRoomWidth ( default: 3)
                RoomSize = FreeCells;
            }

            Rooms.Add(TPair<int, int> (RoomSize, Output->Input->RoomHeight));
            x += RoomSize + 1; // Make border between Rooms

            // Update free cells
            FreeCells = Output->Input->Size.X - Output->Input->BorderSize - x;
        }

        // Custom shuffle
        for (int i = 0; i < Rooms.Num(); i++)
        {
            const int Index = FMath::RandRange(0, Rooms.Num() - 1);
            if (Index != i)
            {
                Rooms.Swap(i, Index);
            }
        }

        // Place rooms
        int RoomX = Output->Input->BorderSize;
        int PositionOnFloor = 0;

        for (auto &RoomData : Rooms){
            const int Length = RoomData.Key;
            const int Height = RoomData.Value;
            
            TPair<FIntPoint, FIntPoint> RoomBounds = GetRoomArea({RoomX, y}, Length, Height);

            Output->Rooms->AddExistRoom(UMapRoom::MAKE(this,
                                                       Length, RoomBounds.Key, RoomBounds.Value,
                                                       GlobalIndex, FRoomCoordinates(PositionOnFloor, FloorNumber)));
            
            RoomArea.Add(TPair<FIntPoint, FIntPoint> (RoomBounds.Key, RoomBounds.Value));

            RoomX += Length + 1;

            PositionOnFloor++;
            GlobalIndex++;
        }

        y += Output->Input->RoomHeight + 1;
        FloorNumber++;
    }

    Output->FloorsCount = FloorNumber;

    // Mark all walls
    for (int Fx = 0; Fx < Output->Input->Size.X; Fx++){
        for (int Fy = 0; Fy < Output->Input->Size.Y; Fy++){
            bool Found = false;

            for (auto &Area : RoomArea){
                const FIntPoint Start = Area.Key;
                const FIntPoint Finish = Area.Value;
                
                if (Start.X <= Fx && Fx <= Finish.X){
                    if (Start.Y <= Fy && Fy <= Finish.Y){
                        Found = true;
                        break;
                    }
                }
            }

            if (!Found){
                
                Output->GeneratorData.WallItem->Place(this,
                                                      {Fx, Fy}, Output);
            }
        }
    }
}
void UDefaultMapGenerator::GeneratePasses(UMapOutput* Output)
{
    
}
void UDefaultMapGenerator::SetRoomFlags(UMapOutput* Output)
{
    
}
void UDefaultMapGenerator::PlaceStructures(UMapOutput* Output)
{
    
}
