// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CF_Ship_CPP.h"


#include "CPP_PlayerController.generated.h"

/**
 * 
 */


UCLASS()
class MOVESTUFFINSPACE_API ACPP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPP_PlayerController();

	UFUNCTION(BlueprintCallable)
	FHitResult OnClickHit();

	UPROPERTY(BlueprintReadWrite)
	int32 HitName;

	UFUNCTION(BlueprintCallable, Category = Widget)
	void ResetWidgetOpened(UUserWidget* OpenedWidget);


protected:
	virtual void BeginPlay();

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Zoom Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;

	/** Reset Zoom Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ResetZoomAction;

	/** Pause Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	/** Pause Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseMenuAction;

	/** Click Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ClickAction;

	///////////////////////////////////////////////////////////////
	// Controlled pawn
	APawn* ControlledPawn = nullptr;
	// Default Arm Length
	float DefaultArmLength;
	// Ship reference for communication with planet when implementing Add Destination 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Destination, meta = (AllowPrivateAccess = "true"))
	ACF_Ship_CPP* ShipReference = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Destination, meta = (AllowPrivateAccess = "true"))
	bool bIsAddingDestination = false;


	///////////////////////////////////////////////////////////////
	// Default Movement speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float DefaultMovementSpeed = 15.f;
	// MovementSpeedModifier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float MovementSpeedModifier = 1;
	// Zoom amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom, meta = (AllowPrivateAccess = "true"))
	float ZoomMultiplier = 1;
	UPROPERTY(EditDefaultsOnly, Category = Zoom)
	UCurveFloat* CurveFloat;
	// Circle radius that restricts the player movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom, meta = (AllowPrivateAccess = "true"))
	float CircleRadius;

	///////////////////////////////////////////////////////////////
	// On Click UI Reference to the Widget Blueprint class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> PlanetWidgetBlueprintClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> ShipWidgetBlueprintClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> PauseMenuBlueprintClass;

	UUserWidget* PauseMenuInstance;

	/////////////////////////////////////////////////////////////////
	// Game Instance 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameInstance, meta = (AllowPrivateAccess = "true"))
	class UCpp_GameInstance* GameInstance;


private:
	void Move(const FInputActionValue& Value);

	void MoveConstraints();

	void Zoom(const FInputActionValue& Value);

	void ResetZoom();

	void PauseGameTime();

	void PauseMenu();

};
