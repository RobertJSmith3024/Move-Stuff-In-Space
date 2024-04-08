// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_GameInstance.h"

EMyGameState UCpp_GameInstance::GetCurrentGameState()
{
	return CurrentGameState;
}

void UCpp_GameInstance::SetCurrentGameState(EMyGameState NewState)
{
	CurrentGameState = NewState;
}

void UCpp_GameInstance::UpdateHighestScore(int32 NewScore)
{
	if (NewScore > HighestScore)
	{
		HighestScore = NewScore;
	}
}
