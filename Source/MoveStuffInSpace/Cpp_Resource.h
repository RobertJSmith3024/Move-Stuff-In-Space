// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Cpp_Resource.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MOVESTUFFINSPACE_API UCpp_Resource : public UDataAsset
{
	GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Resource;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentStorage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStorage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LastTickStorage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseProduction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentProduction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LastTickProduction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ResourceValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DropResource;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAccept;

protected:

private:


};
