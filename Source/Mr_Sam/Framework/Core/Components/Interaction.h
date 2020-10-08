// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"

#include "../GameCharacter.h"

#include "Interaction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MR_SAM_API UInteraction : public UActorComponent
{
	GENERATED_BODY()

	// Camera animation vars
    FTransform CameraTransform;
	FTransform CameraInitialTransform_Relative;

	bool IsFinishAnimation = false;
public:	
	UInteraction();

	// Properties:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    UCameraComponent *InteractCamera = nullptr;

	// ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    bool UseOwnCamera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    float CameraAnimationTime = 0;

	// ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
    bool IsShowHUD = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
    bool IsInInteraction = false;

	// ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
    UTimelineComponent *CameraTimeline = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    UCurveFloat *CameraTimelineCurve = nullptr;

	// ---
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Properties")
	AGameCharacter *InteractInitiator = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
	APlayerController *InteractController = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
	UCameraComponent *InteractInitiatorCamera = nullptr;
	
protected:
	virtual void BeginPlay() override;

	// Timeline events bindings
	UFUNCTION()
    void UpdateCameraLocation(const float TimelineProgress);

	UFUNCTION()
    void FinishCameraAnimation();
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	// API:
	UFUNCTION(BlueprintCallable, Category="Properties")
	void SetTimeline(UTimelineComponent *TimelineComponent);

	// ---
	UFUNCTION(BlueprintCallable, Category="Properties")
    void Interact(AGameCharacter *InitiatorCharacter, UCameraComponent *CameraComponent);
	
	UFUNCTION(BlueprintCallable, Category="Properties")
    void FinishInteract();
};
