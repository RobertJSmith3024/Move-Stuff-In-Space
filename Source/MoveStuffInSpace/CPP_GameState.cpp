// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameState.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/DateTime.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_Planet.h"
#include "Cpp_GameInstance.h"

ACPP_GameState::ACPP_GameState()
{
	PrimaryActorTick.bCanEverTick = true;
	SetInitialGameTime();
}

void ACPP_GameState::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UCpp_GameInstance>(GetGameInstance());
}
void ACPP_GameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameSpeed != 0 && GameInstance && GameInstance->GetCurrentGameState() != EMyGameState::GameOver)
	{
		CalculateTime(DeltaTime);
		SetClockCalendar();

		ProcessEvents();

		if (TimeDelegate.IsBound()) {
			TimeDelegate.Broadcast();
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f"), TotalGameTime);
	}
}

void ACPP_GameState::ScheduleEvent(float GameTimeInHours, const FEventDelegate& EventDelegate)
{
	ScheduleRepeatingEvent(GameTimeInHours, 0, EventDelegate);
}

void ACPP_GameState::ScheduleRepeatingEvent(float GameTimeInHours, float IntervalInHours, const FEventDelegate& EventDelegate)
{
	// Create a new scheduled event
	struct FScheduledEvent NewEvent;
	NewEvent.GameTimeInHours = GameTimeInHours;
	NewEvent.IntervalInHours = IntervalInHours;
	NewEvent.EventDelegate = EventDelegate;

	// Add the event to the array
	ScheduledEvents.Add(NewEvent);
}

void ACPP_GameState::ScheduleRepeatingEventInDay(float GameTimeInDays, float IntervalInDays, const FEventDelegate& EventDelegate)
{
	// Create a new scheduled event
	struct FScheduledEvent NewEvent;
	NewEvent.GameTimeInHours = GameTimeInDays * DayMultiplier;
	NewEvent.IntervalInHours = IntervalInDays * DayMultiplier;
	NewEvent.EventDelegate = EventDelegate;

	// Add the event to the array
	ScheduledEvents.Add(NewEvent);
}

void ACPP_GameState::ProcessEvents()
{
	// Process scheduled events
	//float CurrentGameTime = UGameplayStatics::GetTimeSeconds(GetWorld());
	//UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentGameTime);
	for (int32 i = 0; i < ScheduledEvents.Num(); ++i)
	{
		FScheduledEvent& Event = ScheduledEvents[i];
		if (TotalGameTime >= Event.GameTimeInHours)
		{
			// Execute the event delegate
			Event.EventDelegate.ExecuteIfBound();

			// Check if it's a recurring event
			if (Event.IntervalInHours > 0)
			{
				// Schedule the next occurrence
				Event.GameTimeInHours += Event.IntervalInHours;
			}
			else
			{
				// Remove the one-time event from the array
				ScheduledEvents.RemoveAt(i);
				--i; // Decrement the index as the array size has changed
			}
		}
	}
}

void ACPP_GameState::UpdateEventDelegate(int Identifier, const FEventDelegate& EventDelegate)
{
	ScheduledEvents[Identifier].EventDelegate = EventDelegate;
}

TSubclassOf<ACpp_Planet> ACPP_GameState::GetRandomPlanet(TArray<TSubclassOf<ACpp_Planet>> randomPlanets)
{
	// Check if the array is empty
	if (randomPlanets.Num() == 0)
	{
		return nullptr; // Return nullptr when the array is empty
	}

	// Generate a random index
	int32 randomIndex = FMath::RandRange(0, randomPlanets.Num() - 1);

	// Return the UClass pointer of the random element
	return randomPlanets[randomIndex];
}

void ACPP_GameState::CalculateTime(float DeltaTime)
{
	CalculateGameTime(DayCounter, GameTime, TotalGameTime, DeltaTime, GameTime);
}

void ACPP_GameState::SetClockCalendar()
{
	// Set seconds (Assume GameTime in hour)
	Seconds = GameTime * 3600;
	int32 MinutesQuotient = FMath::DivideAndRoundDown(Seconds, 60);
	Seconds = FMath::Fmod(Seconds, 60.f);
	// Set minutes 
	int32 HoursQuotient = FMath::DivideAndRoundDown(MinutesQuotient, 60);
	Minutes = FMath::Fmod(MinutesQuotient, 60.f);
	// Set hours
	Hours = FMath::Fmod(HoursQuotient, 24.f);

	// Set Day
	Day += DayCounter;
	DayPlayed += DayCounter;
	if (Day > FDateTime::DaysInMonth(Year, Month))
	{
		Day = 1;
		++Month;
	}
	if (Month > 12)
	{
		Month = 1;
		++Year;
	}
	DateTimeStruct = FDateTime(Year, Month, Day, Hours, Minutes, Seconds);
	//UE_LOG(LogTemp, Warning, TEXT("%d-%d/%d/%d"), Hours, Year, Month, Day);
}

void ACPP_GameState::CalculateGameTime(int32& DayCounterLIB, float& OutGameTime, float& TotalInGameTime, float InDeltaTime, float InGameTime)
{
	// Calculate total in game time (in hours)
	TotalInGameTime += InDeltaTime;
	// Game Time in hour
	float CurrentGameTime = InDeltaTime + InGameTime;
	// Get the remainder of the CurrentGameTime / 24
	OutGameTime = FMath::Fmod(CurrentGameTime, 24.f);
	// Get the quotient  of the Current Game Time / 24
	DayCounterLIB = FMath::DivideAndRoundDown(CurrentGameTime, 24.f);
}

void ACPP_GameState::SetGameSpeedFastForward()
{
	++GameSpeed;
	GameSpeed = fmin(GameSpeed, MaxGameSpeed);
	//Global fast forward.
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), GameSpeed);
	GameInstance->SetCurrentGameState(EMyGameState::FastForward);
}

void ACPP_GameState::ResetGameSpeed()
{
	GameSpeed = DefaultGameSpeed;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), GameSpeed);
	GameInstance->SetCurrentGameState(EMyGameState::InGame);
}

void ACPP_GameState::PauseGameSpeed()
{
	//Global slow motion.
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0001);
	GameInstance->SetCurrentGameState(EMyGameState::Pause);

}

UUserWidget* ACPP_GameState::OpenWidget(APlayerController* PlayerController, TSubclassOf<UUserWidget> Widget)
{
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACPP_GameState::OpenWidget(): Widget is InValid"));
		return nullptr;
	}
	// Check if the Widget Blueprint Class is set
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACPP_GameState::OpenWidget(): PlayerController is InValid"));
		return nullptr;
	}
	// Create the widget
	UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(PlayerController, Widget);
	if (!WidgetInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACPP_GameState::OpenWidget(): WidgetInstance is InValid"));
		return nullptr;
	}
	// Add the widget to the viewport
	WidgetInstance->AddToViewport();
	return WidgetInstance;
	
}

void ACPP_GameState::OnGameOverState()
{
	// if a planet dies, show game over screen
	if (true)
	{
		GameInstance->SetCurrentGameState(EMyGameState::GameOver);
		if (!GameOverWidgetBlueprintClass)
		{
			return;
		}
		GameInstance->UpdateHighestScore(DayPlayed);
		OpenWidget(GetWorld()->GetFirstPlayerController(), GameOverWidgetBlueprintClass);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

//void ACPP_GameState::SetCurrentGameState(EGameState NewState)
//{
//	CurrentGameState = NewState;
//}

void ACPP_GameState::SetInitialGameTime()
{
	GameTime = Hours + Minutes / 60 + Seconds / 3600;
}
	
