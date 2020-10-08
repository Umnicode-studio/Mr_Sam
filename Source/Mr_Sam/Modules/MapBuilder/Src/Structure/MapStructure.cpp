#include "MapStructure.h"

UMapStructure::UMapStructure()
{
    
}

// API:
int UMapStructure::GetStructureWidth() const
{
    int Width = 0;

    for (const FMapStructureChunk &Chunk : this->Chunks) Width += Chunk.Width;
    return Width;
}

// ---
UMapStructure *UMapStructure::MAKE(UObject* WorldContextObject, const FString StructureId,
                                   const int StructureGlobalPosition,
                                   const TArray<FMapStructureChunk> StructureChunks,
                                   const TArray<FString> StructureProtectedBy)
{
    if (IsValid(WorldContextObject))
    {
        UMapStructure *Structure = NewObject<UMapStructure>(WorldContextObject);

        if (IsValid(Structure))
        {
            Structure->Id = StructureId;
            Structure->GlobalPosition = StructureGlobalPosition;
            
            Structure->Chunks = StructureChunks;
            Structure->ProtectedBy = StructureProtectedBy;
            
            return Structure;
        }
    }
    
    return nullptr;
}