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
    struct FPass{
        ESideEnum Side;
        TArray <TTuple <FIntPoint, UMapRoom *, bool>> Positions;

        FPass(const ESideEnum &Side){
            this->Side = Side;
        }
    };

    // Lambdas
    auto IsUsed = [](const UMapRoom *Room, const TArray <UMapRoom *> &Used){
        if (IsValid(Room)) {
            return Used.Contains(Room);
        }

        return false;
    };
    auto IsObstacle = [](FIntPoint Position, UMapOutput &Output){
        return UGeneratorUtils::IsStepsHere(Output.GeneratorData.StepsItem->Id, Position, &Output) ||       
               UGeneratorUtils::IsWallHere(Output.GeneratorData.WallItem->Id, Position, &Output);
    };
    auto CheckRoomX = [&](int x, int IsOnOtherSteps, UMapRoom *CurrentRoom, UMapRoom *TargetRoom,
            UMapOutput &MOutput){
        bool Result;

        if (IsOnOtherSteps == 1) { // On current
            Result = UGeneratorUtils::IsStepsHere(MOutput.GeneratorData.StepsItem->Id,
                                                  {x, CurrentRoom->Finish.Y}, Output) &&
                     !IsObstacle({x, TargetRoom->Finish.Y}, MOutput);
            
        }
        else if (IsOnOtherSteps == 2) { // On target
            Result = UGeneratorUtils::IsStepsHere(MOutput.GeneratorData.StepsItem->Id,
                                                  {x, TargetRoom->Finish.Y}, Output) &&
                     !IsObstacle({x, CurrentRoom->Finish.Y}, MOutput);
        }
        else{
            Result = !IsObstacle({x, CurrentRoom->Finish.Y}, MOutput) &&
                     !IsObstacle({x, TargetRoom->Finish.Y}, MOutput);
        }

        return Result;
    };

    TArray <UMapRoom *> History;
    TArray <UMapRoom *> Used;

    // Init
    History.Add(Output->Rooms->GetRoomByIndex(0));
    Used.Add(Output->Rooms->GetRoomByIndex(0));
    
    while (History.Num() > 0){
        UMapRoom *Current = History[History.Num() - 1];
        TArray <FPass> Passes = {S_Up, S_Down, S_Left, S_Right};
        
        // Get all available positions for the pass
        auto Neighbors = UGeneratorUtils::GetRoomNeighbors(Current, Output);
        for (FRoomNeighbor &Neighbor : Neighbors){
            TEnumAsByte<ESideEnum> &Side = Neighbor.Side;
            UMapRoom *NRoom = Neighbor.Room;
            
            if (IsUsed(NRoom, Used)) continue;

            if (Side == S_Up || Side == S_Down) { // x axis check
                for (int x = FMath::Max(NRoom->Start.X, Current->Start.X);
                     x <= FMath::Min(NRoom->Finish.X, Current->Finish.X); x++) {

                    // check current x
                    bool Add = true;
                    int IsOnOtherSteps = 0; // O - not; 1 - steps in current room; 2 - steps in target room

                    if (UGeneratorUtils::IsStepsHere(Output->GeneratorData.StepsItem->Id,
                                                    {x, Current->Finish.Y}, Output)){
                        IsOnOtherSteps = 1;
                    }
                    else if (UGeneratorUtils::IsStepsHere(Output->GeneratorData.StepsItem->Id,
                                                          {x, NRoom->Finish.Y}, Output)){
                        IsOnOtherSteps = 2;
                    }

                    // Check steps whole all their width
                    for (int Cx = x; Cx < x + Output->Input->StepWidth; Cx++) {
                        if (!CheckRoomX(Cx, IsOnOtherSteps, Current, NRoom, *Output)) {
                            Add = false;
                            break;
                        }
                    }

                    // Add position to list ( If possible )
                    if (Add) { 
                        if (Side == S_Up) {
                            Passes[0].Positions.Add(MakeTuple(FIntPoint (x,NRoom->Start.Y +
                                                              FMath::FloorToInt(Output->Input->RoomHeight / 2)),
                                                              NRoom, IsOnOtherSteps > 0));
                        }
                        else {
                            Passes[1].Positions.Add(MakeTuple(FIntPoint (x, Current->Start.Y +
                                                              FMath::FloorToInt(Output->Input->RoomHeight / 2)),
                                                              NRoom, IsOnOtherSteps > 0));
                        }
                    }
                }
            } else { // no checks for left/right
                if (Side == S_Left) {
                    Passes[2].Positions.Add(MakeTuple(FIntPoint(NRoom->Finish.X + 1,
                                                           NRoom->Start.Y), NRoom, false));
                }
                else{
                    Passes[3].Positions.Add(MakeTuple(FIntPoint(Current->Finish.X + 1,
                                                           Current->Start.Y), NRoom, false));
                }
            }
        }

        // check for deadend
        bool IsDeadend = true;
        for (auto &Array : Passes){
            if (Array.Positions.Num() != 0){
                IsDeadend = false;
                break;
            }
        }

        if (IsDeadend){
            History.Pop(); // jump to the previous step
        }
        else {
            // place pass
            while (true) {
                auto &Source = Passes[FMath::RandRange(0, 3)];

                if (Source.Positions.Num() == 0) continue;

                const auto &Tuple = Source.Positions[FMath::RandRange(0, Source.Positions.Num() - 1)];
                FIntPoint Position = Tuple.Get<0>();
                UMapRoom *Room = Tuple.Get<1>();
                const bool IsOnOtherSteps = Tuple.Get<2>();
                
                if (Source.Side == S_Left || Source.Side == S_Right) {
                    for (int y = Position.Y; y < Position.Y + Output->Input->RoomHeight; y++){ // remove walls
                        FIntPoint ItemPosition(Position.X, y);
                        
                        Output->Items->RemoveItemsById(ItemPosition, Output->GeneratorData.WallItem->Id);
                    }

                    // Place door
                    Output->GeneratorData.DoorItem->Size = {1, Output->Input->RoomHeight};
                    Output->GeneratorData.DoorItem->Place(this, Position, Output);
                }
                else {
                    GEngine->AddOnScreenDebugMessage(-1, 35.0f, FColor::Yellow, "Down");
                    
                    Output->GeneratorData.StepsItem->Size = {Output->Input->StepWidth,
                                                             FMath::CeilToInt(Output->Input->RoomHeight * 1.5) + 1};
                    const int WallLine = Position.Y + FMath::CeilToInt(Output->Input->RoomHeight / 2);

                    // fix overlapped steps
                    if (IsOnOtherSteps){
                        UMapItemOutput *OverlappedSteps = Output->Items->FindItemThatPossesPointByLayer(Position,
                                                                               Output->GeneratorData.DefaultLayer);
                        if (OverlappedSteps){
                            if (OverlappedSteps->Position.Y < Position.Y){ // Up
                                Output->GeneratorData.StepsItem->Size = {Output->Input->StepWidth,
                                                                         Output->Input->RoomHeight + 1};
                                
                                Position.Y += FMath::CeilToInt(Output->Input->RoomHeight / 2);
                            }else{ // Down
                                OverlappedSteps->Size = {Output->Input->StepWidth,
                                                         Output->Input->RoomHeight + 1};
                                OverlappedSteps->Position.Y += FMath::CeilToInt(Output->Input->RoomHeight / 2);
                            }
                        }
                    }
  
                    // Make hole in a wall
                    for (int x = Position.X; x < Position.X + Output->Input->StepWidth; x++){
                        FIntPoint ItemPosition = {x, WallLine};

                        Output->Items->RemoveItemsById(ItemPosition, Output->GeneratorData.WallItem->Id);
                        Output->GeneratorData.WallWithHoleItem->Place(this, ItemPosition, Output);
                    }

                    // Place steps
                    Output->GeneratorData.StepsItem->Place(this, Position, Output);
                }
                
                // Write our room to history
                History.Add(Room);
                Used.Add(Room);

                // link rooms between themselves
                FIntPoint PassPosition = Position;

                if (!IsOnOtherSteps && Source.Side != S_Up){ // set position to hole border
                    PassPosition.Y += FMath::CeilToInt(Output->Input->RoomHeight / 2);
                }

                Current->Passes.Add(FRoomPass(Room->GlobalPosition, Source.Side, PassPosition));
                Room->Passes.Add(FRoomPass(Current->GlobalPosition, Source.Side, PassPosition));

                break;
            }
        }
    }    
}

void UDefaultMapGenerator::MergeWalls(UMapOutput* Output)
{
    auto CheckItem = [](FIntPoint &Pos, UMapLayer *Layer,
                        const TMap<FIntPoint, bool> &UsedCells, UMapOutput *Output) -> bool
    {
        if (!IsValid(Output) || !IsValid(Layer)) return false;
        if (UsedCells.Contains(Pos)) return false;
        
        UMapItemOutput *Item = Output->Items->FindItem(Pos, Layer);
        if (!IsValid(Item)) return false;
        
        return Item->Id == Output->GeneratorData.WallItem->Id;
    };
    
    auto GetGroupSize = [](const FIntPoint &GroupStart, const FIntPoint &GroupFinish)
    {
        return GroupFinish - GroupStart + FIntPoint(1, 1);
    };
    
    UMapItemOutputArray *NewArray = NewObject<UMapItemOutputArray>(this);
    TMap <FIntPoint, bool> UsedCells;

    for (int x = 0; x < Output->Input->Size.X; x++)
    {
        for (int y = 0; y < Output->Input->Size.Y; y++){
            FIntPoint Temp(x, y);
            
            if (!UsedCells.Contains(Temp))
            {
                // Get all items in position
                TArray<UMapItemOutput *> ItemsArray = Output->Items->GetItemsByPosition(Temp);
                UMapItemOutput *Item = nullptr;
        
                // Find wall
                for (UMapItemOutput *I : ItemsArray)
                {
                    if (IsValid(I) && I->Layers.Num() > 0 && I->Id == Output->GeneratorData.WallItem->Id)
                    {
                        Item = I;
                        break;
                    }
                }

                if (Item != nullptr)
                {
                    const FIntPoint GroupStart = Item->Position;
                    FIntPoint GroupFinish = Item->Position + Item->Size - FIntPoint(1, 1); 

                    bool IsGroupExtended;
                    
                    do
                    {
                        bool ToRight = true;
                        bool ToBottom = true;

                        // Check edges of the group
                        // Extend to right
                        for (int PosY = GroupStart.Y; PosY <= GroupFinish.Y; PosY++)
                        {
                            Temp = FIntPoint(GroupFinish.X + 1, PosY);
                            if (!CheckItem(Temp, Item->Layers[0],
                                           UsedCells, Output))
                            {
                                ToRight = false;
                                break;
                            }
                        }
                        if (ToRight)
                        {
                            GroupFinish.X++;
                        }

                        // Extend to bottom
                        for (int PosX = GroupStart.X; PosX <= GroupFinish.X; PosX++)
                        {
                            Temp = FIntPoint(PosX, GroupFinish.Y + 1);
                            if (!CheckItem(Temp, Item->Layers[0],
                                           UsedCells, Output))
                            {
                                ToBottom = false;
                                break;
                            }
                        }
                        if (ToBottom)
                        {
                            GroupFinish.Y++;
                        }

                        IsGroupExtended = ToRight || ToBottom;
                    }
                    while (IsGroupExtended);
                    
                    // Mark cells in group as used
                    for (int Px = GroupStart.X; Px <= GroupFinish.X; Px++)
                    {
                        for (int Py = GroupStart.Y; Py <= GroupFinish.Y; Py++)
                        {
                            UsedCells.Add(FIntPoint(Px, Py), true);
                        }
                    }
                    
                    NewArray->AddExistItem(UMapItemOutput::MAKE(this, Item->Actor, Item->Id,
                                                                GroupStart,
                                                                GetGroupSize(GroupStart, GroupFinish), Item->Layers));
                }
            }
        }
    }

    // Add all non-wall items to NewArray
    for (UMapItemOutput *Item : Output->Items->GetContent())
    {
        if (IsValid(Item) && Item->Id != Output->GeneratorData.WallItem->Id)
        {
            NewArray->AddExistItem(Item);
        }
    }

    Output->Items = NewArray;
}

void UDefaultMapGenerator::SetRoomFlags(UMapOutput* Output)
{
    
}
void UDefaultMapGenerator::PlaceStructures(UMapOutput* Output)
{
    
}
