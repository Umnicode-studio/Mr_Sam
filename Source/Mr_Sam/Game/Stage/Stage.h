// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "../../Framework/Utils/FrameworkUtils.h"
#include "Mr_Sam/Modules/MapBuilder/Src/MapGenerator.h"

#include "Stage.generated.h"

UCLASS()
class MR_SAM_API AStage : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	USceneComponent *StageRootComponent = nullptr;

	FVector GetActorScaleToTile(const FVector &ActorSize, const FIntPoint &ItemSize) const;
	static float GetZValueForActor(const TArray<UMapLayer *> &Layers);
public:	
	AStage();

	// Properties:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	TSubclassOf<UMapInput> Input;

	// Primitives:
	UPROPERTY(VisibleAnywhere, Category="Properties")
	UMapOutput *LevelSource = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	FVector TileSize;
	
	UPROPERTY(VisibleAnywhere, Category="Properties")
	bool IsLevelLoaded = false;

	UPROPERTY(VisibleAnywhere, Category="Properties")
	TArray <AStaticMeshActor *> StageTiles;

	// API:
	UFUNCTION(BlueprintCallable, Category="Stage")
	bool LoadStage(UMapOutput *Output);
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
