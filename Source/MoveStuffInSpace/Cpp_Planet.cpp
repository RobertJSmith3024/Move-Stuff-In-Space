// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Planet.h"
#include "Components/StaticMeshComponent.h"  // Include this for the mesh component
#include "Components/SphereComponent.h"  // Include this for the spherical collision
#include "Cpp_Resources.h"
#include "Cpp_UpgradeList.h"
#include "Components/WidgetComponent.h"

// Sets default values
ACpp_Planet::ACpp_Planet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh component and attach it to the root
	PlanetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));
	RootComponent = PlanetMesh;

	// Create the spherical collision component and attach it to the root
	PlanetCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PlanetCollision"));
	PlanetCollision->SetupAttachment(RootComponent);

	// Create the widget component and set it as the RootComponent
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);

	// Create an instance of your actor component
	ResourceComponent = CreateDefaultSubobject<UCpp_Resources>(TEXT("YourActorComponent"));

	UpgradeListComponent = CreateDefaultSubobject<UCpp_UpgradeList>(TEXT("UpgradeListComponent"));
}

// Called when the game starts or when spawned
void ACpp_Planet::BeginPlay()
{
	Super::BeginPlay();
	ResetZeroResourceTimer();
}

// Called every frame
void ACpp_Planet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACpp_Planet::CreateBaseResourceProduction(UCpp_Resources* ResourcesToSet, 
	int32 RandomRange, int32 NearestToMultiplier, UCpp_Resources* PlayerResources)
{
	bool bAtLeastOneNegative = false;
	// Iterate through the array of Resource structs
	for (int32 i = 0; i < ResourcesToSet->Array.Num(); ++i)
	{
		// Generate a random base production value within the range
		int32 RandomBase = FMath::RandRange(-RandomRange, RandomRange);
		// Get Current base from PlayerResources
		int32 CurrentBase = PlayerResources->Array[i].CurrentProduction / 10;
		int32 numLoops = 0;

		while (CurrentBase + RandomBase < 0 || RandomBase == 0)
		{
			RandomBase = FMath::RandRange(-RandomRange, RandomRange);
			numLoops += 1;
			if (numLoops > 15)
			{
				RandomBase = FMath::RandRange(1, RandomRange);
			}
		}

		// Check if at least one value is positive for each index
		if (RandomBase < 0)
		{
			bAtLeastOneNegative = true;
		}

		int32 RandomBaseProduction = RandomBase * NearestToMultiplier;

		// Set the random base production value for the current Resource struct
		ResourcesToSet->Array[i].BaseProduction = RandomBaseProduction;
	}

	// If none are negative, retrieve the resource produced the most and provide a negative value for that resource in new planet
	if (!bAtLeastOneNegative)
	{
		int32 MaxProduction = PlayerResources->Array[0].CurrentProduction; // Initialize with the first element
		int32 MaxIndex = 0; // Initialize with the index of the first element

		for (int32 i = 1; i < PlayerResources->Array.Num(); ++i)
		{
			if (PlayerResources->Array[i].CurrentProduction > MaxProduction)
			{
				// Update the maximum value and its index
				MaxProduction = PlayerResources->Array[i].CurrentProduction;
				MaxIndex = i;
			}
		}
		ResourcesToSet->Array[MaxIndex].BaseProduction = -FMath::RandRange(2, RandomRange)* NearestToMultiplier;
	}
}

void ACpp_Planet::SetCurrentResourceProduction(UCpp_Resources* ResourcesToSet)
{
	for (int32 i = 0; i < ResourcesToSet->Array.Num(); ++i)
	{
		ResourcesToSet->Array[i].CurrentProduction = ResourcesToSet->Array[i].BaseProduction;
	}
}

void ACpp_Planet::SetPlanetStartingStorage(UCpp_Resources* ResourcesToSet, int32 StorageMultiplier)
{
	for (int32 i = 0; i < ResourcesToSet->Array.Num(); ++i)
	{
		int32 BaseProduction = ResourcesToSet->Array[i].BaseProduction;
		int32 NewCurrentStorage = BaseProduction * StorageMultiplier;

		// Ensure the new current storage is positive
		if (NewCurrentStorage < 0)
		{
			NewCurrentStorage *= -1;
		}

		// Set the current storage value for the current resource
		ResourcesToSet->Array[i].CurrentStorage = NewCurrentStorage;
	}
}

void ACpp_Planet::SetMaxStorage(UCpp_Resources* ResourcesToSet)
{
	for (int32 i = 0; i < ResourcesToSet->Array.Num(); ++i)
	{
		ResourcesToSet->Array[i].MaxStorage = 1000;
	}
}

void ACpp_Planet::HomeSetBaseProduction(UCpp_Resources* ResourcesToSet)
{
	for (int32 i = 0; i < ResourcesToSet->Array.Num(); ++i)
	{
		switch (i)
		{
		case 0:
		ResourcesToSet->Array[i].BaseProduction = 30;
		break;

		case 1:
		ResourcesToSet->Array[i].BaseProduction = 30;
		break;

		case 2:
		ResourcesToSet->Array[i].BaseProduction = 30;
		break;

		default:
		break;
		}
		
	}
}

void ACpp_Planet::CountDownZeroResourceTimer()
{
	CurrentZeroResourceTime -= 1;
}

void ACpp_Planet::ResetZeroResourceTimer()
{
	CurrentZeroResourceTime = ZeroResourceTimer;
}

float ACpp_Planet::CalculateTimeProgress()
{
	return (float)CurrentZeroResourceTime / ZeroResourceTimer;
}

FText ACpp_Planet::GetName()
{
	return Name;
}

void ACpp_Planet::SetName(FText name)
{
	Name = name;
}
