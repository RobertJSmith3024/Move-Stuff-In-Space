// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cpp_Planet.h"
#include "Cpp_Planet_Home.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MOVESTUFFINSPACE_API FPlanetDetails
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InitialProduction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ResourceValue;
};

UCLASS()
class MOVESTUFFINSPACE_API ACpp_Planet_Home : public ACpp_Planet
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACpp_Planet_Home();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateBaseResourceProduction(UCpp_Resources* ResourcesToSet);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	int32 BaseProduction;

	UPROPERTY(EditAnywhere)
	TArray<FPlanetDetails> StartingInfo;

private:

	

};
