// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_ShipSpawner.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CF_Ship_CPP.h"

// Sets default values
ACpp_ShipSpawner::ACpp_ShipSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	// Create and set up the collision component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACpp_ShipSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACpp_ShipSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACpp_ShipSpawner::SpawnShip(TSubclassOf<ACF_Ship_CPP> Ship, FName SpawnShipName)
{
    if (!Ship)
    {
        // Handle null ship subclass
        UE_LOG(LogTemp, Error, TEXT("Invalid ship subclass provided!"));
    }
	
	// Get the actor's current transform
	FTransform SpawnTransform = GetActorTransform();

	// Modify the location component of the transform to add an offset of +200 in the X direction
	FVector NewLocation = SpawnTransform.GetLocation() + FVector(200.f, 0.f, 0.f);
	SpawnTransform.SetLocation(NewLocation);

	// Spawn the ship at the modified transform
	ACF_Ship_CPP* NewShip = GetWorld()->SpawnActor<ACF_Ship_CPP>(Ship, SpawnTransform);
	if (NewShip)   
	{
		NewShip->SetName(SpawnShipName);
		// Optionally, you can perform additional initialization for the spawned ship here    
	}    
	else
	{    
		// Handle failure to spawn 
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn ship!"));
	}

}

void ACpp_ShipSpawner::StoreShip(class ACF_Ship_CPP* Ship)
{
	// Adds a ship to Array and moves ship to a location the player cannot see.
	// Before function is called, make sure to check if ship wants to be added and ship has collided with Station
	StoredShips.Add(Ship);
	Ship->SetActorLocation({ 0.0f, 0.0f, -10000.0f });
}

void ACpp_ShipSpawner::MoveShipToVisibleLocation(ACF_Ship_CPP* Ship)
{
	FVector CurrentLocation = GetActorLocation();
	Ship->SetActorLocation(CurrentLocation);
}


