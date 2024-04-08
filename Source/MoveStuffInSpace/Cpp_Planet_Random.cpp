// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Planet_Random.h"
#include "Cpp_Resources.h"

ACpp_Planet_Random::ACpp_Planet_Random()
{
}

void ACpp_Planet_Random::BeginPlay()
{
	Super::BeginPlay();
 //   CreateBaseResourceProduction();
	//SetCurrentResourceProduction();
 //   SetMaxStorage();
 //   SetCurrentStorage();
}

void ACpp_Planet_Random::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACpp_Planet_Random::CreateBaseResourceProduction(UCpp_Resources* ResourcesToSet)
{
    // Iterate through the array of Resource structs
    for (int32 i = 0; i < ResourcesToSet->Array.Num(); ++i)
    {
        // Generate a random base production value within the range of 30 to -30
        int32 RandomBaseProduction = FMath::RandRange(-30, 30);

        // Set the random base production value for the current Resource struct
        ResourcesToSet->Array[i].BaseProduction = RandomBaseProduction;
    }

    // Check if at least one value is positive for each index
    bool bAtLeastOnePositive = false;
    for (int32 i = 0; i < ResourcesToSet->Array.Num(); ++i)
    {
        if (ResourcesToSet->Array[i].BaseProduction > 0)
        {
            bAtLeastOnePositive = true;
            break;
        }
    }

    // If none are positive, randomly select one index and make its value positive
    if (!bAtLeastOnePositive)
    {
        int32 IndexToMakePositive = FMath::RandRange(0, ResourcesToSet->Array.Num() - 1);
        ResourcesToSet->Array[IndexToMakePositive].BaseProduction = FMath::RandRange(1, 30);
    }
}
