// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_Planet.generated.h"

UCLASS()
class MOVESTUFFINSPACE_API ACpp_Planet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_Planet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void CreateBaseResourceProduction(UCpp_Resources* ResourcesToSet, 
		int32 RandomRange, int32 NearestToMultiplier, UCpp_Resources* PlayerResources);

	UFUNCTION(BlueprintCallable)
	void SetCurrentResourceProduction(UCpp_Resources* ResourcesToSet);
	
	UFUNCTION(BlueprintCallable)
	void SetPlanetStartingStorage(UCpp_Resources* ResourcesToSet, int32 StorageMultiplier);

	UFUNCTION(BlueprintCallable)
	void SetMaxStorage(UCpp_Resources* ResourcesToSet);

	UFUNCTION(BlueprintCallable)
	void HomeSetBaseProduction(UCpp_Resources* ResourcesToSet);

	UFUNCTION(BlueprintCallable)
	void CountDownZeroResourceTimer();

	UFUNCTION(BlueprintCallable)
	void ResetZeroResourceTimer();

	UFUNCTION(BlueprintCallable)
	float CalculateTimeProgress();

	UFUNCTION(BlueprintCallable)
	FText GetName();

	UFUNCTION(BlueprintCallable)
	void SetName(FText name);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Declare a UWidgetComponent pointer to hold the created widget component instance
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UWidgetComponent* WidgetComponent;

	// Declare an instance of your actor component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCpp_Resources* ResourceComponent;

	// Declare an instance of your actor component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCpp_UpgradeList* UpgradeListComponent;




private:
	// Mesh component for the planet
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Planet", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PlanetMesh;

	// Spherical collision component for the planet
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Planet", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* PlanetCollision;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet", meta = (AllowPrivateAccess = "true"))
	bool bHasAtLeastOneZeroResource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet", meta = (AllowPrivateAccess = "true"))
	int32 ZeroResourceTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet", meta = (AllowPrivateAccess = "true"))
	int32 CurrentZeroResourceTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet", meta = (AllowPrivateAccess = "true"))
	FText Name;
};