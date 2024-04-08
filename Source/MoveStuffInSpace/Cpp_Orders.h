// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpp_Planet.h"
#include "Cpp_Orders.generated.h"

// Order status
UENUM(BlueprintType)
enum class EOrderState : uint8
{
	Load UMETA(DisplayName = "Load"),
	Unload UMETA(DisplayName = "Unload"),
	None UMETA(DisplayName = "None")
};

UCLASS(BlueprintType, Blueprintable)
class MOVESTUFFINSPACE_API UCpp_Orders : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCpp_Orders();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orders, meta = (AllowPrivateAccess = true))
	AActor* SelectedPlanet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orders, meta = (AllowPrivateAccess = true))
	EOrderState OrderState;
		
};
