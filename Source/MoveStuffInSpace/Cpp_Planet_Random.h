// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cpp_Planet.h"
#include "Cpp_Planet_Random.generated.h"

/**
 * 
 */
UCLASS()
class MOVESTUFFINSPACE_API ACpp_Planet_Random : public ACpp_Planet
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACpp_Planet_Random();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateBaseResourceProduction(UCpp_Resources* ResourcesToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};
