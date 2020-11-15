// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../../UI/LoadingScreen/LoadingScreenWidget.h"
#include "../Globals.h"


#include "FrameworkGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MR_SAM_API AFrameworkGameMode : public AGameModeBase
{
	GENERATED_BODY()

	void RemoveLoadingScreenWidgets();
public:
	AFrameworkGameMode();

	virtual void StartPlay() override;
	
	// Level loading:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|LoadingScreen")
	TSubclassOf<class ULoadingScreenWidget> LoadingScreenWidgetClass;

	// API:
	UFUNCTION(BlueprintCallable, Category="Framework|Registry")
    bool LoadGameLevel(FName LevelName, float MinimumDelay = 2.0f);

protected:
	// Level loading properties:
	UPROPERTY()
	ULoadingScreenWidget *LoadingScreenWidget = nullptr;

	UPROPERTY()
	FName LoadingLevelName;

	// Events:
	void LoadGameLevel_Listener() const;
};
