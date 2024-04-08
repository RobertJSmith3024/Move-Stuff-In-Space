// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CF_Ship_CPP.generated.h"


UCLASS()
class MOVESTUFFINSPACE_API ACF_Ship_CPP : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACF_Ship_CPP();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetBaseStorage(UCpp_Resources* ResourcesToSet);

	UFUNCTION(BlueprintCallable)
	FName GetName();

	UFUNCTION(BlueprintCallable)
	void SetName(FName NewName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Declare an instance of your actor component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCpp_Resources* ResourceComponent;

	// Add Static Mesh Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* StaticMeshComponent;

	// Declare an instance of your actor component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCpp_UpgradeList* UpgradeListComponent;

	// Declare a spline component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int32 Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int32 LoadingRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int32 UnloadingRate;


private:
	int32 baseStorage;

		


};
