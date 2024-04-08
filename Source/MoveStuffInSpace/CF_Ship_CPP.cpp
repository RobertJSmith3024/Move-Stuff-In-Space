// Fill out your copyright notice in the Description page of Project Settings.


#include "CF_Ship_CPP.h"
#include "Cpp_Resources.h"
#include "Cpp_UpgradeList.h"
#include "Components/SplineComponent.h"

// Sets default values
ACF_Ship_CPP::ACF_Ship_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create an instance of your actor component
	ResourceComponent = CreateDefaultSubobject<UCpp_Resources>(TEXT("YourActorComponent"));

	UpgradeListComponent = CreateDefaultSubobject<UCpp_UpgradeList>(TEXT("UpgradeListComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);

	// Variables initialisation
	LoadingRate = 100;
	UnloadingRate = 100;
}

// Called when the game starts or when spawned
void ACF_Ship_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACF_Ship_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACF_Ship_CPP::SetBaseStorage(UCpp_Resources* ResourcesToSet)
{
	for (int32 i = 0; i < ResourcesToSet->Array.Num(); ++i)
	{
		ResourcesToSet->Array[i].MaxStorage = 500;
	}
}

FName ACF_Ship_CPP::GetName()
{
	return Name;
}

void ACF_Ship_CPP::SetName(FName NewName)
{
	Name = NewName;
}

