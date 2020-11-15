// (c) DPACK.inc

#pragma once
#define _WIN32_WINNT_WIN10_RS2
#define _WIN32_WINNT_WIN10_RS1

#define _WIN32_WINNT_WIN10_TH2

#include "CoreMinimal.h"

#include "../Core/Components/GameObject.h"
#include "../Core/GameInstance/Registry.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FrameworkUtils.generated.h"

/**
 * 
 */
UCLASS()
class MR_SAM_API UFrameworkUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category="Framework|Utils", meta=(WorldContext="WorldContextObject"))
	static void IsActorGameObject(AActor *Actor, bool &Result, UGameObjectComponent *&GameObject);

	UFUNCTION(BlueprintCallable, Category="Framework|Utils")
	static FVector GetStaticMeshSize(UStaticMesh *Mesh);
};
