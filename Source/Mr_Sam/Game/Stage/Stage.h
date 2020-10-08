#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Mr_Sam/Modules/MapBuilder/Src/IO/MapInput.h"

#include "Stage.generated.h"

UCLASS()
class MR_SAM_API AStage : public AActor
{
	GENERATED_BODY()

public:	
	AStage();

	// Properties:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	TSubclassOf<UMapInput> Input;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Tiles")
	FVector2D TileSize;

	// Primitives:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Tiles")
	UStaticMesh *WallMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Tiles")
	UStaticMesh *WallWithHoleMesh = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Tiles")
	UStaticMesh *StepsMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Tiles")
	UStaticMesh *DoorMesh = nullptr;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
