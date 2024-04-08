// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpp_Resources.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MOVESTUFFINSPACE_API FResourceStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Resource;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentStorage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinStorage;

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

    // Add any other properties as needed
};

UCLASS(BlueprintType, Blueprintable)
class MOVESTUFFINSPACE_API UCpp_Resources : public UActorComponent
{
	GENERATED_BODY()
	
public:

    UCpp_Resources();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FResourceStruct> Array;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<class UCpp_Resource>> Resource;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<class UCpp_Resource*> ConstructedResource;

    UFUNCTION(BlueprintCallable)
    int32 GetCurrentStorage(int32 index);
    UFUNCTION(BlueprintCallable)
    void SetCurrentStorage(int32 index, int32 newStorage);


    UFUNCTION(BlueprintCallable)
    int32 GetMinStorage(int32 index);
    UFUNCTION(BlueprintCallable)
    void SetMinStorage(int32 index, int32 newMinStorage);

    UFUNCTION(BlueprintCallable)
    int32 GetMaxStorage(int32 index);
    UFUNCTION(BlueprintCallable)
    void SetMaxStorage(int32 index, int32 newMaxStorage);

    UFUNCTION(BlueprintCallable)
    int32 GetBaseProduction(int32 index);
    UFUNCTION(BlueprintCallable)
    void SetBaseProduction(int32 index, int32 newBaseProduction);

    UFUNCTION(BlueprintCallable)
    int32 GetCurrentProduction(int32 index);
    UFUNCTION(BlueprintCallable)
    void SetCurrentProduction(int32 index, int32 newCurrentProduction);

    UFUNCTION(BlueprintCallable)
    int32 AddToStorage(int32 ArrayIndex, int32 AmountToAdd);

    UFUNCTION(BlueprintCallable)
    int32 CheckMinStorage(int32 ArrayIndex, int32 AmountToAdd);

    UFUNCTION(BlueprintCallable)
    int32 CPPROnDropOffLogic(int32 indexRef);
    UFUNCTION(BlueprintCallable)
    void ProductionPerTick();
    UFUNCTION(BlueprintCallable)
    int32 SendStorageUpdate(int32 indexRef);
    UFUNCTION(BlueprintCallable)
    int32 SendProductionUpdate(int32 indexRef);

    UFUNCTION(BlueprintCallable)
    bool SetbAccept(int32 indexRef);

protected:

private:

};
