// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Delegates/Delegate.h"

#include "CPP_GameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMultiEventDelegate, float, GameTimeToExecute, float, EventInterval);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimeDelegate);
DECLARE_DYNAMIC_DELEGATE(FEventDelegate);


// Struct to hold information about a scheduled event
USTRUCT(BlueprintType)
struct FScheduledEvent
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GameTimeInHours;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IntervalInHours;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEventDelegate EventDelegate;
};

UCLASS()
class MOVESTUFFINSPACE_API ACPP_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ACPP_GameState();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	////////////////////////////////////////////////////
	// Game Time Setting Functions
	void CalculateTime(float DeltaTime);
	void SetClockCalendar();
	UFUNCTION(BlueprintPure)
	void CalculateGameTime(int32& GameDay, float& OutGameTime, float& TotalInGameTime, float InDeltaTime, float InGameTime);

	////////////////////////////////////////////////////////
	// Game Speed Setting Functions
	UFUNCTION(BlueprintCallable)
	void SetGameSpeedFastForward();
	UFUNCTION(BlueprintCallable)
	void ResetGameSpeed();
	UFUNCTION(BlueprintCallable)
	void PauseGameSpeed();

	// Function to open Widget
	UFUNCTION(BlueprintCallable, Category = "UI")
	static UUserWidget* OpenWidget(APlayerController* PlayerController, TSubclassOf<UUserWidget> Widget);

	// On Game Over State
	UFUNCTION(BlueprintCallable, Category = GameOver)
	void OnGameOverState();

	//// Getter and Setter
	//void SetCurrentGameState(EGameState NewState);

	// Function to schedule a one-time event after a specified game time
	UFUNCTION(BlueprintCallable, Category = "Game Timer")
	void ScheduleEvent(float GameTimeInHours, const FEventDelegate& EventDelegate);

	// Function to schedule a recurring event with a specified interval
	UFUNCTION(BlueprintCallable, Category = "Game Timer")
	void ScheduleRepeatingEvent(float GameTimeInHours, float IntervalInHours, const FEventDelegate& EventDelegate);

	// Function to schedule a recurring event with a specified interval (InDay)
	UFUNCTION(BlueprintCallable, Category = "Game Timer")
	void ScheduleRepeatingEventInDay(float GameTimeInDays, float IntervalInDays, const FEventDelegate& EventDelegate);

	void ProcessEvents();

	// Function to update the event delegate
	UFUNCTION(BlueprintCallable, Category = "Game Timer")
	void UpdateEventDelegate(int Identifier, const FEventDelegate& EventDelegate);

	///////////////////////////////////////////////////////////////////////////
	// Planet Spawning Functions
	UFUNCTION(BlueprintCallable, Category = "Planets")
	TSubclassOf<class ACpp_Planet> GetRandomPlanet(TArray<TSubclassOf<class ACpp_Planet>> randomPlanets);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planets")
	TArray<TSubclassOf<class ACpp_Planet>> RandomPlanets;


	UPROPERTY(BlueprintAssignable)
	FMultiEventDelegate MultiEventDelegate;
	UPROPERTY(BlueprintAssignable)
	FTimeDelegate TimeDelegate;

	// Reference to the Widget Blueprint class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetBlueprintClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetBlueprintClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> InGameHUDWidgetBlueprintClass;
private:
	// Array to store scheduled events
	TArray<FScheduledEvent> ScheduledEvents;

	//////////////////////////////////////////////////////////
	// Game Speed Setting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSpeedSetting, meta = (AllowPrivateAccess = true))
	float GameSpeed = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSpeedSetting, meta = (AllowPrivateAccess = true))
	float DefaultGameSpeed = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameSpeedSetting, meta = (AllowPrivateAccess = true))
	float MaxGameSpeed = 3.f;

	/** 
	Game time unit is in hour 
	Real Time : GameSpeed  = Time in game
	e.g. 1s:1 = 1 game hour
	1s:60 = 1 game minute
	1s:3600 = real time
	1m:2.5 = 1 game day
	1hr:150 = 1 game day 
	*/

	// Multiplier to convert the days into total hours
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	float DayMultiplier = 24;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	float TotalGameTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	float GameTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	FDateTime DateTimeStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	int Year = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	int Month = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	int Day = 1;
	int32 DayCounter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	int Hours = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	int Minutes = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	int Seconds = 0;

	// Days last for
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameTimeSetting, meta = (AllowPrivateAccess = true))
	int DayPlayed = 0;

	// The Game Instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance", meta = (AllowPrivateAccess = true))
	class UCpp_GameInstance* GameInstance;


private:
	void SetInitialGameTime();



};
