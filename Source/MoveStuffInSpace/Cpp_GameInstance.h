// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Cpp_GameInstance.generated.h"

/**
 * 
 */

 // Game State
UENUM(BlueprintType)
enum class EMyGameState : uint8
{
	MainMenu UMETA(DisplayName = "MainMenu"),
	InGame UMETA(DisplayName = "InGame"),
	Pause UMETA(DisplayName = "Pause"),
	FastForward UMETA(DisplayName = "FastForward"),
	GameOver UMETA(DisplayName = "GameOver"),
	None UMETA(DisplayName = "None")
};

UCLASS()
class MOVESTUFFINSPACE_API UCpp_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Getter and Setter
	UFUNCTION(BlueprintCallable)
	EMyGameState GetCurrentGameState();
	UFUNCTION(BlueprintCallable)
	void SetCurrentGameState(EMyGameState NewState);
	UFUNCTION(BlueprintCallable)
	void UpdateHighestScore(int32 NewScore);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameState, meta = (AllowPrivateAccess = true))
	EMyGameState CurrentGameState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Volume, meta = (AllowPrivateAccess = true))
	float MusicVolume = 0.6;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Volume, meta = (AllowPrivateAccess = true))
	int32 HighestScore;
};
