// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpp_UpgradeList.generated.h"


UCLASS(BlueprintType, Blueprintable)
class MOVESTUFFINSPACE_API UCpp_UpgradeList : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCpp_UpgradeList();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UCpp_Upgrade>> UpgradeArray;

protected:


private:

		
};
