// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Cpp_Upgrade.generated.h"

/**
 * 
 */

UCLASS(BlueprintType, Blueprintable)
class MOVESTUFFINSPACE_API UCpp_Upgrade : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	int32 GetCost();
	UFUNCTION(BlueprintCallable)
	void SetCost(int32 newCost);

	UFUNCTION(BlueprintCallable)
	int32 GetLevel();
	UFUNCTION(BlueprintCallable)
	void SetLevel(int32 newLevel);

	UFUNCTION(BlueprintCallable)
	FName GetName();
	UFUNCTION(BlueprintCallable)
	void SetName(FName newName);

	UFUNCTION(BlueprintCallable)
	virtual void Upgrade(class UCpp_Resources* ResourceClass);

protected:

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	int32 Cost;

	UPROPERTY(EditAnywhere)
	int32 Level;


private:


};
