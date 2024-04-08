// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CPP_CameraPawn.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "CPP_GameState.h"
#include "Blueprint/UserWidget.h"
#include "CPP_GameState.h"
#include "Cpp_Planet.h"
#include "CF_Ship_CPP.h"
#include "Cpp_GameInstance.h"
#include "CPP_GameState.h"

ACPP_PlayerController::ACPP_PlayerController()
{
}

FHitResult ACPP_PlayerController::OnClickHit()
{
	return FHitResult();
}

void ACPP_PlayerController::ResetWidgetOpened(UUserWidget* OpenedWidget)
{
	OpenedWidget->UUserWidget::RemoveFromParent();
}

void ACPP_PlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	GetWorld()->bIsCameraMoveableWhenPaused = true;
	GameInstance = Cast<UCpp_GameInstance>(GetGameInstance());

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	SetShowMouseCursor(true);

	// Get the controlled pawn
	ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		DefaultArmLength = ControlledPawn->GetComponentByClass<USpringArmComponent>()->TargetArmLength;
	}
}


void ACPP_PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup move input events
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Move);

		// Zoom events
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Zoom);

		// Reset Zoom events
		EnhancedInputComponent->BindAction(ResetZoomAction, ETriggerEvent::Triggered, this, &ACPP_PlayerController::ResetZoom);

		//// Pause events
		//EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ACPP_PlayerController::PauseGameTime);

		// Pause Menu events
		EnhancedInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Started, this, &ACPP_PlayerController::PauseMenu);
		PauseMenuAction->bTriggerWhenPaused = true;
		// Click events
		// to be implemented in Blueprint editor
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACPP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_PlayerController::Move(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();

	//APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		// find out which way is forward
		const FRotator Rotation = ControlledPawn->GetControlRotation();

		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = YawRotation.Vector();

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

		// add movement
		ControlledPawn->AddActorLocalOffset(ForwardDirection * MovementVector.Y * DefaultMovementSpeed * MovementSpeedModifier, true);
		ControlledPawn->AddActorLocalOffset(RightDirection * MovementVector.X * DefaultMovementSpeed * MovementSpeedModifier, true);

		MoveConstraints();
	}
}

void ACPP_PlayerController::MoveConstraints()
{
	// Movement constraints
	FVector CircleCenter(0, 0, 0); // Center of the circle

	// Player's current position
	FVector PlayerPosition = ControlledPawn->GetActorLocation();

	// Calculate the distance between the player and the circle center
	float DistanceToCenter = FVector::Distance(PlayerPosition, CircleCenter);

	// Check if the player is outside the circle
	if (DistanceToCenter > CircleRadius)
	{
		// Calculate the direction vector from the circle center to the player
		FVector Direction = (PlayerPosition - CircleCenter).GetSafeNormal();

		// Move the player back along the direction vector until the distance equals the radius
		PlayerPosition = CircleCenter + (Direction * CircleRadius);
	}

	ControlledPawn->SetActorLocation(FVector(PlayerPosition.X, PlayerPosition.Y, ControlledPawn->GetActorLocation().Z));
}

void ACPP_PlayerController::Zoom(const FInputActionValue& Value)
{
	float ZoomAxis = Value.Get<float>();

	//APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		float CurrentArmLength = ControlledPawn->GetComponentByClass<USpringArmComponent>()->TargetArmLength;
		CurrentArmLength += ZoomAxis * ZoomMultiplier;
		ControlledPawn->GetComponentByClass<USpringArmComponent>()->TargetArmLength = CurrentArmLength;
	}
}

void ACPP_PlayerController::ResetZoom()
{
	ControlledPawn->GetComponentByClass<USpringArmComponent>()->TargetArmLength = DefaultArmLength;
}

void ACPP_PlayerController::PauseGameTime()
{
	//if (UGameplayStatics::GetGlobalTimeDilation(GetWorld()) >= 1)
	//{
	//	//Global slow motion.
	//	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.00001);
	//	GameInstance->SetCurrentGameState(EGameState::Pause);
	//}
	//else
	//{
	//	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
	//	GameInstance->SetCurrentGameState(EGameState::InGame);
	//}
}

void ACPP_PlayerController::PauseMenu()
{
	SetPause(!IsPaused());
	if (IsPaused())
	{
		PauseMenuInstance = ACPP_GameState::OpenWidget(this, PauseMenuBlueprintClass);
	}
	else
	{
		if (!PauseMenuInstance) return;
		PauseMenuInstance->RemoveFromParent();
	}
}








