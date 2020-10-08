// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction.h"

#include "GameObject.h"

UInteraction::UInteraction()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UInteraction::BeginPlay()
{
	Super::BeginPlay();
}

void UInteraction::UpdateCameraLocation(const float TimelineProgress)
{
    APawn *Pawn = dynamic_cast <APawn *> (this->GetOwner());
	if (IsValid(Pawn))
	{
		if (this->IsShowHUD && this->InteractController)
		{
			// Disable input, HUD
			Pawn->DisableInput(this->InteractController);
			this->IsShowHUD = false;
		}
		
		// Convert CameraComponent World transform to relative transform for InteractCamera
		FTransform CameraTransform_Relative;

		if (this->IsFinishAnimation && IsValid(this->InteractInitiatorCamera))
		{
			CameraTransform_Relative = this->InteractInitiatorCamera->GetComponentToWorld() * Pawn->GetTransform().Inverse();
		}else
		{
			CameraTransform_Relative = this->CameraTransform * Pawn->GetTransform().Inverse();
		}

		// Update location/rotation
		this->InteractCamera->SetRelativeLocation(FMath::Lerp(CameraTransform_Relative.GetLocation(), this->CameraInitialTransform_Relative.GetLocation(),
            TimelineProgress));
	
		this->InteractCamera->SetRelativeRotation(FMath::Lerp(CameraTransform_Relative.GetRotation(), this->CameraInitialTransform_Relative.GetRotation(),
            TimelineProgress));
	}
}
void UInteraction::FinishCameraAnimation()
{
	APawn *Pawn = dynamic_cast <APawn *> (this->GetOwner());
	
	if (IsValid(Pawn) && IsValid(this->InteractController))
	{
		if (this->IsFinishAnimation && IsValid(this->InteractInitiator) && IsValid(this->InteractCamera))
		{	
			// UnPossess
			this->InteractController->UnPossess();
			this->InteractController->Possess(this->InteractInitiator);

			UGameObject *PawnGameObject = dynamic_cast<UGameObject *> (Pawn->GetComponentByClass(UGameObject::StaticClass())); // Get game object component
			if (IsValid(PawnGameObject))
			{
				PawnGameObject->IsInteract = true; // Disable interaction flag
			} 

			// Restore camera location/rotation
			this->InteractCamera->SetRelativeLocation(this->CameraInitialTransform_Relative.GetLocation());
			this->InteractCamera->SetRelativeRotation(this->CameraInitialTransform_Relative.GetRotation());

			this->InteractInitiator = nullptr;
			this->InteractController = nullptr;
		}else
		{
			Pawn->EnableInput(this->InteractController); // Enable input only when start interacting
			this->IsShowHUD = true; // Enable HUD; Note that when we are not interact with ActivePawn HUD not showing 
		}
	}
}

void UInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UInteraction::SetTimeline(UTimelineComponent* TimelineComponent)
{
	if (IsValid(TimelineComponent))
	{
		this->CameraTimeline = TimelineComponent;
		
		// Init camera timeline
		if (IsValid(this->CameraTimelineCurve))
		{
			// Bindings
			FOnTimelineFloat TimelineProgress;
			TimelineProgress.BindUFunction(this, FName("UpdateCameraLocation"));

			FOnTimelineEvent TimelineFinish;
			TimelineFinish.BindUFunction(this, FName("FinishCameraAnimation"));
			
			// Timeline params
			this->CameraTimeline->SetTimelineFinishedFunc(TimelineFinish);
			this->CameraTimeline->AddInterpFloat(this->CameraTimelineCurve, TimelineProgress);
			this->CameraTimeline->SetLooping(false);
		} 
	}
}

void UInteraction::Interact(AGameCharacter* InitiatorCharacter, UCameraComponent* CameraComponent)
{
	APlayerController *IController = GetWorld()->GetFirstPlayerController();
	APawn *Pawn = dynamic_cast <APawn *> (this->GetOwner());
	
	// Interaction init
	if (IController && InitiatorCharacter && IsValid(Pawn))
	{
		UGameObject *PawnGameObject = dynamic_cast<UGameObject *> (Pawn->GetComponentByClass(UGameObject::StaticClass())); // Get game object component
		if (IsValid(PawnGameObject))
		{
			PawnGameObject->IsInteract = true; // Enable interaction flag
		} 
		
		// Posses ActivePawn
		IController->UnPossess();
		IController->Possess(Pawn);

		// Camera animation
		if (this->InteractCamera && CameraComponent)
		{	
			// Save camera position
			this->CameraInitialTransform_Relative = this->InteractCamera->GetRelativeTransform();

			// Init camera animation
			this->IsFinishAnimation = false;
			
			// Select interaction mode
			if (this->UseOwnCamera)
			{
				this->CameraTransform = CameraComponent->GetComponentToWorld();

				this->CameraTimeline->SetTimelineLength(this->CameraAnimationTime);
				this->CameraTimeline->PlayFromStart();
			}else
			{
				this->InteractCamera->SetWorldLocation(CameraComponent->GetComponentToWorld().GetLocation());
				this->InteractCamera->SetWorldRotation(CameraComponent->GetComponentToWorld().GetRotation());

				this->FinishCameraAnimation();
			}
			
		}

		this->InteractInitiator = InitiatorCharacter;
		this->InteractInitiatorCamera = CameraComponent;
		
		this->InteractController = IController;
	}
}
void UInteraction::FinishInteract()
{
	if (IsValid(this->InteractCamera) && IsValid(this->InteractController))
	{		
		this->IsFinishAnimation = true;
	
		if (this->UseOwnCamera)
		{
			this->CameraTimeline->ReverseFromEnd();
		}else{
			this->FinishCameraAnimation();
		}
	}
}


