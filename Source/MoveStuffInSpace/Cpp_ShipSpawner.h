// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_ShipSpawner.generated.h"

UCLASS()
class MOVESTUFFINSPACE_API ACpp_ShipSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_ShipSpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void SpawnShip(TSubclassOf<class ACF_Ship_CPP> Ship, FName SpawnShipName);

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void StoreShip(class ACF_Ship_CPP* Ship);

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void MoveShipToVisibleLocation(class ACF_Ship_CPP* Ship);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<TSubclassOf<class ACF_Ship_CPP>> AvailableShips;


	UPROPERTY(EditAnywhere, Category = "YourActor")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "YourActor")
	class USphereComponent* CollisionComponent;

	TArray<class ACF_Ship_CPP*> StoredShips;
private:


};
