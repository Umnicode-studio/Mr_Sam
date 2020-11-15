#include "MapGenerator.h"

#include "Generator/Functions.h"

UDefaultMapGenerator::UDefaultMapGenerator()
{
    
}

bool UDefaultMapGenerator::Init(UMapOutput *Output)
{
    Super::Init(Output);
    
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
                Output->GeneratorData.WallItem->Size = {1, 1}; // Size of wall is 1x1 tile
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
                                                 "Warning there's no valid Wall item in " + Output->Input->LevelName);
            }

            if (IsValid(Output->Input->WallWithHoleItem))
            {
                Output->GeneratorData.WallWithHoleItem = Output->Input->WallWithHoleItem.GetDefaultObject();
                Output->GeneratorData.WallItem->Size = {1, 1};
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
    Super::CleanUp(Output);
}

void UDefaultMapGenerator::GenerateRooms(UMapOutput *Output)
{
    Super::CleanUp(Output);
    
    auto GetRoomArea = [](const FIntPoint StartPos, const int32 Length, const int32 Height){
        return TPair<FIntPoint, FIntPoint> (FIntPoint(StartPos.X, StartPos.Y),
               FIntPoint(StartPos.X + Length - 1, StartPos.Y + Height - 1));
    };
    
    TArray <TPair <FIntPoint, FIntPoint>> RoomArea;

    int32 GlobalIndex = 0;
    int32 FloorNumber = 0;

    int32 y = Output->Input->BorderSize;

    // generate floor
    do
    {
        // create rooms
        int32 x = Output->Input->BorderSize;
        TArray <TPair <int32, int32>> Rooms;

        int32 FreeCells = Output->Input->Size.X - Output->Input->BorderSize - x;
        while (FreeCells >= Output->Input->MinRoomWidth){ // place Rooms
            int32 RoomSize;
            
            if (FreeCells > Output->Input->MinRoomWidth){ // Prevent using int32 distribution with zero range
                // select random size
                int32 MaxLength = Output->Input->Size.X - 1 - x;
                if (Output->Input->MaxRoomWidth >= Output->Input->MinRoomWidth) MaxLength = Output->Input->MaxRoomWidth; // set max Room width
                
                RoomSize = FMath::RandRange(Output->Input->MinRoomWidth, MaxLength);
            }
            else{
                RoomSize = Output->Input->MinRoomWidth;
            }

            if (FreeCells - RoomSize - 1 < Output->Input->MinRoomWidth) { // prevent creating Rooms that smaller that MinRoomWidth ( default: 3)
                RoomSize = FreeCells;
            }

            Rooms.Add(TPair<int32, int32> (RoomSize, Output->Input->RoomHeight));
            x += RoomSize + Output->GeneratorData.WallItem->Size.X; // Make border between Rooms

            // Update free cells
            FreeCells = Output->Input->Size.X - Output->Input->BorderSize - x;
        }

        // Custom shuffle
        FFrameworkCppUtils::ShuffleTArray(Rooms);

        // Place rooms
        int32 RoomX = Output->Input->BorderSize;
        int32 PositionOnFloor = 0;

        for (auto &RoomData : Rooms){
            const int32 Length = RoomData.Key;
            const int32 Height = RoomData.Value;
            
            TPair<FIntPoint, FIntPoint> RoomBounds = GetRoomArea({RoomX, y}, Length, Height);

            Output->Rooms->AddExistRoom(UMapRoom::MAKE(this,
                                                       Length, RoomBounds.Key, RoomBounds.Value,
                                                       GlobalIndex, FRoomCoordinates(PositionOnFloor, FloorNumber)));
            
            RoomArea.Add(TPair<FIntPoint, FIntPoint> (RoomBounds.Key, RoomBounds.Value));

            RoomX += Length + Output->Input->SpaceBetweenRooms.X;

            PositionOnFloor++;
            GlobalIndex++;
        }

        y += Output->Input->RoomHeight + Output->Input->SpaceBetweenRooms.Y;
        FloorNumber++;
    }
    while(y < Output->Input->Size.Y - Output->Input->BorderSize - Output->Input->SpaceBetweenRooms.Y); 

    Output->FloorsCount = FloorNumber;

    // Mark all walls
    for (int32 Fx = 0; Fx < Output->Input->Size.X; Fx++){
        for (int32 Fy = 0; Fy < Output->Input->Size.Y; Fy++){
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
    Super::GeneratePasses(Output);
    
    struct FPass{
        ESideEnum Side;
        TArray <TTuple <FIntPoint, UMapRoom *, EOverlappedPassType>> Positions;

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
    auto CheckRoomX = [&](int32 x, EOverlappedPassType OverlapType, UMapRoom *CurrentRoom,
        UMapRoom *TargetRoom, UMapOutput &MOutput){
        
        bool Result;

        if (OverlapType == T_Current) { // On current
            Result = UGeneratorUtils::IsStepsHere(MOutput.GeneratorData.StepsItem->Id,
                                                  {x, CurrentRoom->Finish.Y}, Output) &&
                     !IsObstacle({x, TargetRoom->Finish.Y}, MOutput);
            
        }
        else if (OverlapType == T_Target) { // On target
            Result = !IsObstacle({x, CurrentRoom->Finish.Y}, MOutput) &&
                      UGeneratorUtils::IsStepsHere(MOutput.GeneratorData.StepsItem->Id,
                                                  {x, TargetRoom->Finish.Y}, Output) ;
        }
        else if (OverlapType == T_Both)
        {
            Result = UGeneratorUtils::IsStepsHere(MOutput.GeneratorData.StepsItem->Id,
                                                  {x, CurrentRoom->Finish.Y}, Output) &&
                     UGeneratorUtils::IsStepsHere(MOutput.GeneratorData.StepsItem->Id,
                                                  {x, TargetRoom->Finish.Y}, Output);
        }
        else{
            Result = !IsObstacle({x, CurrentRoom->Finish.Y}, MOutput) &&
                     !IsObstacle({x, TargetRoom->Finish.Y}, MOutput);
        }

        return Result;
    };

    const float HalfRoomHeight = Output->Input->RoomHeight / 2;

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

            TArray<FPass> NormalSteps_Passes = {{S_Up}, {S_Down}};
            TArray<FPass> OverlappedSteps_Passes = {{S_Up}, {S_Down}};
            
            if (Side == S_Up || Side == S_Down) { // x axis check
                for (int32 x = FMath::Max(NRoom->Start.X, Current->Start.X);
                     x <= FMath::Min(NRoom->Finish.X, Current->Finish.X); x++) {

                    // check current x
                    bool Add = true;
                    EOverlappedPassType OverlappingType = T_None;

                    if (UGeneratorUtils::IsStepsHere(Output->GeneratorData.StepsItem->Id,
                                                    {x, Current->Finish.Y}, Output)){
                        OverlappingType = T_Current;
                    }
                    else if (UGeneratorUtils::IsStepsHere(Output->GeneratorData.StepsItem->Id,
                                                          {x, NRoom->Finish.Y}, Output))
                    {
                        if (OverlappingType != T_None)
                        {
                            OverlappingType = T_Both;
                        }else
                        {
                            OverlappingType = T_Target;
                        }
                    }

                    // Check steps whole all their width
                    for (int32 Cx = x; Cx < x + Output->Input->StepWidth; Cx++) {
                        if (!CheckRoomX(Cx, OverlappingType, Current, NRoom, *Output)) {
                            Add = false;
                            break;
                        }
                    }

                    // Add position to list ( If possible )
                    if (Add) {
                        int32 RoomY;
                        if (Side == S_Up)
                        {
                            // Swap overlap room to opposite
                            if (OverlappingType == T_Target)
                            {
                                OverlappingType = T_Current;
                            }else if (OverlappingType == T_Current)
                            {
                                OverlappingType = T_Target;
                            }
                            
                            RoomY = NRoom->Start.Y;
                        }else
                        {
                            RoomY = Current->Start.Y;
                        }
                        
                        auto Tuple = MakeTuple(FIntPoint (x,RoomY +
                                                          FMath::FloorToInt(HalfRoomHeight)),
                                                          NRoom, OverlappingType);
                        
                        if (OverlappingType == T_None) {
                            // Small hack, it's possible because values in enum are equal to array index
                            NormalSteps_Passes[Side].Positions.Add(Tuple);
                        }
                        else {
                            OverlappedSteps_Passes[Side].Positions.Add(Tuple);
                        }
                        
                    }
                }
            }
            else { // no checks for left/right
                if (Side == S_Left) {
                    Passes[2].Positions.Add(MakeTuple(FIntPoint(NRoom->Finish.X + 1,
                                                           NRoom->Start.Y), NRoom, T_None));
                }
                else{
                    Passes[3].Positions.Add(MakeTuple(FIntPoint(Current->Finish.X + 1,
                                                           Current->Start.Y), NRoom, T_None));
                }
            }

            // Remove all not overlapped steps ( Used to move priority to long steps )
            for (int32 c = 0; c < OverlappedSteps_Passes.Num(); c++)
            {   
                if (OverlappedSteps_Passes[c].Positions.Num() != 0)
                {
                    Passes[c].Positions.Append(OverlappedSteps_Passes[c].Positions);
                }
                else
                {
                    Passes[c].Positions.Append(NormalSteps_Passes[c].Positions);
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

                const auto &Tuple = Source.Positions[FMath::RandRange(0,
                    Source.Positions.Num() - 1)];

                // Divide tuple
                FIntPoint ItemPosition = Tuple.Get<0>();
                UMapRoom *Room = Tuple.Get<1>();
                const EOverlappedPassType &OverlappingType = Tuple.Get<2>();
                
                if (Source.Side == S_Left || Source.Side == S_Right) {
                    for (int32 y = ItemPosition.Y; y < ItemPosition.Y + Output->Input->RoomHeight; y++){ // remove walls
                        FIntPoint WallPosition(ItemPosition.X, y);
                        
                        Output->Items->RemoveItemsById(WallPosition, Output->GeneratorData.WallItem->Id);
                    }

                    // Place door
                    Output->GeneratorData.DoorItem->Size = {1, Output->Input->RoomHeight};
                    Output->GeneratorData.DoorItem->Place(this, ItemPosition, Output);
                }
                else {
                    FIntPoint ItemSize = {Output->Input->StepWidth,
                                          FMath::CeilToInt(HalfRoomHeight * 3) + 1};
                    
                    const int32 WallLine = ItemPosition.Y + FMath::CeilToInt(HalfRoomHeight);

                    // Fix overlapping
                    if (OverlappingType != T_None)
                    {
                        if (OverlappingType == T_Current)
                        {
                            ItemPosition.Y += FMath::CeilToInt(HalfRoomHeight);
                        }else if (OverlappingType == T_Target){ 
                            ItemSize.Y -= FMath::CeilToInt(HalfRoomHeight);
                        }else { // T_Both
                            ItemPosition.Y += FMath::CeilToInt(HalfRoomHeight);
                            ItemSize.Y -= FMath::CeilToInt(HalfRoomHeight);
                        }
                    }

                    // Make hole in a wall
                    for (int32 x = ItemPosition.X; x < ItemPosition.X + Output->Input->StepWidth; x++){
                        FIntPoint WallPosition = {x, WallLine};

                        Output->Items->RemoveItemsById(WallPosition, Output->GeneratorData.WallItem->Id);
                        Output->GeneratorData.WallWithHoleItem->Place(this, WallPosition,
                                                                      Output);
                    }

                    // Place steps
                    Output->GeneratorData.StepsItem->Size = ItemSize;
                    Output->GeneratorData.StepsItem->Place(this, ItemPosition, Output);
                }
                
                // Write our room to history
                History.Add(Room);
                Used.Add(Room);
                    
                // link rooms between themselves
                Current->Passes.Add(FRoomPass(Room->GlobalPosition, Source.Side, ItemPosition));
                Room->Passes.Add(FRoomPass(Current->GlobalPosition, Source.Side, ItemPosition));
                break;
            }
        }
    }    
}
void UDefaultMapGenerator::MergeWalls(UMapOutput* Output)
{
    Super::MergeWalls(Output);
    
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

    for (int32 x = 0; x < Output->Input->Size.X; x++)
    {
        for (int32 y = 0; y < Output->Input->Size.Y; y++){
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
                        for (int32 PosY = GroupStart.Y; PosY <= GroupFinish.Y; PosY++)
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
                        for (int32 PosX = GroupStart.X; PosX <= GroupFinish.X; PosX++)
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
                    for (int32 Px = GroupStart.X; Px <= GroupFinish.X; Px++)
                    {
                        for (int32 Py = GroupStart.Y; Py <= GroupFinish.Y; Py++)
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
    Super::SetRoomFlags(Output);
}
void UDefaultMapGenerator::PlaceStructures(UMapOutput* Output)
{
    Super::PlaceStructures(Output);
}