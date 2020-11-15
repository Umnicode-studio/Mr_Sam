// (c) DPACK.inc

#include "FrameworkCharacter.h"
#include "Kismet/GameplayStatics.h"

AFrameworkCharacter::AFrameworkCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Enable run physics without controller
	UCharacterMovementComponent *MovementComponent = this->GetCharacterMovement();
	if (IsValid(MovementComponent))
	{
		MovementComponent->bRunPhysicsWithNoController = true;
	}

	// Create GameObjectComponent
	this->GameObject = CreateDefaultSubobject<UGameObjectComponent>(FName("GameObject"));
}

void AFrameworkCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFrameworkCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AFrameworkCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Death API:
void AFrameworkCharacter::Death(FDeathRules Rules)
{
	// Enable ragdoll physics
	if (IsValid(Rules.RagdollMeshComponent))
	{
		Rules.RagdollMeshComponent->SetSimulatePhysics(Rules.EnableRagdoll);
	}

	// Block or enable input
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (IsValid(PlayerController))
	{
		if (Rules.DisableInput)
		{
			this->DisableInput(PlayerController);
		}else
		{
			this->EnableInput(PlayerController);
		}
	}

	// Change health
	this->GameObject->Health.SetValue(this, Rules.NewHealth, Rules.ChangeHealthSilently);
	
	this->OnDeath();
}

// Auto death API:
void AFrameworkCharacter::SetAutoDeathRules(const FAutoDeathRules Rules)
{
	// Bind or unbind AutoDeath_HealthListener to GameObject->Health delegate
	if (this->AutoDeathRules.IsEnabled != Rules.IsEnabled)
	{
		FSmartInt &Health = this->GameObject->Health;
		if (Rules.IsEnabled)
		{
			Health.GetDelegateHolder(this)->
			                            OnValueChanged.AddDynamic(this,
			                            	&AFrameworkCharacter::AutoDeath_HealthListener);
		}
		else
		{
			Health.GetDelegateHolder(this)->
			                            OnValueChanged.RemoveDynamic(this,
			                            	&AFrameworkCharacter::AutoDeath_HealthListener);
		} 
	}

	this->AutoDeathRules.DeathRules.ChangeHealthSilently = true;
	this->AutoDeathRules = Rules;
}
FAutoDeathRules AFrameworkCharacter::GetAutoDeathRules() const
{
	return this->AutoDeathRules;
}

void AFrameworkCharacter::AutoDeath_HealthListener(const int Health)
{
	if (Health < this->AutoDeathRules.MinimalHealth)
	{
		this->Death(this->AutoDeathRules.DeathRules);
	}
}