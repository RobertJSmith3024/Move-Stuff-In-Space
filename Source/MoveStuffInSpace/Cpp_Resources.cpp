// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Resources.h"

UCpp_Resources::UCpp_Resources()
{
}

int32 UCpp_Resources::GetCurrentStorage(int32 index)
{
	return Array[index].CurrentStorage;
}

void UCpp_Resources::SetCurrentStorage(int32 index, int32 newStorage)
{
	Array[index].CurrentStorage = newStorage;
}

int32 UCpp_Resources::GetMinStorage(int32 index)
{
    return Array[index].MinStorage;
}

void UCpp_Resources::SetMinStorage(int32 index, int32 newMinStorage)
{
    Array[index].MinStorage = newMinStorage;
}

int32 UCpp_Resources::GetMaxStorage(int32 index)
{
	return Array[index].MaxStorage;
}

void UCpp_Resources::SetMaxStorage(int32 index, int32 newMaxStorage)
{
	Array[index].MaxStorage = newMaxStorage;
}

int32 UCpp_Resources::GetBaseProduction(int32 index)
{
	return Array[index].BaseProduction;
}

void UCpp_Resources::SetBaseProduction(int32 index, int32 newBaseProduction)
{
	Array[index].BaseProduction = newBaseProduction;
}

int32 UCpp_Resources::GetCurrentProduction(int32 index)
{
	return Array[index].CurrentProduction;
}

void UCpp_Resources::SetCurrentProduction(int32 index, int32 newCurrentProduction)
{
	Array[index].CurrentProduction = newCurrentProduction;
}

int32 UCpp_Resources::AddToStorage(int32 ArrayIndex, int32 AmountToAdd)
{
    int32 ExcessStorage;

    // If bAccept for resource is set to false then return without transferring anything.
    if (Array[ArrayIndex].bAccept == false)
    {
        ExcessStorage = AmountToAdd;
        return ExcessStorage;
    }

    if (ArrayIndex >= 0 && ArrayIndex < Array.Num())
    {
        int32 SpaceAvailable = Array[ArrayIndex].MaxStorage - Array[ArrayIndex].CurrentStorage;

        if (AmountToAdd > SpaceAvailable)
        {
            // If production exceeds available space, add only up to the max storage
            Array[ArrayIndex].CurrentStorage = Array[ArrayIndex].MaxStorage;
            // Handle excess resources (you can store or use them as needed)
            ExcessStorage = AmountToAdd - SpaceAvailable;
            // For now, let's just print a message
            UE_LOG(LogTemp, Warning, TEXT("Excess production for resource %s: %d"), *Array[ArrayIndex].Resource.ToString(), ExcessStorage);
            return ExcessStorage;
        }
        else
        {
            // If there is enough space, add all the production
            Array[ArrayIndex].CurrentStorage += AmountToAdd;
            ExcessStorage = 0;
            return ExcessStorage;
        }
    }
    else
    {
        // Handle invalid array index (you can log an error or handle it as appropriate)
        UE_LOG(LogTemp, Error, TEXT("Invalid array index: %d"), ArrayIndex);
        ExcessStorage = 0;
        return ExcessStorage;
    }
}

int32 UCpp_Resources::CheckMinStorage(int32 ArrayIndex, int32 AmountToAdd)
{
    int32 CurrentStorage = Array[ArrayIndex].CurrentStorage;
    int32 MinStorage = Array[ArrayIndex].MinStorage;

    // Calculate the desired storage after adding AmountToAdd
    int32 DesiredStorage = CurrentStorage + AmountToAdd;

    // Ensure that DesiredStorage doesn't go below MinStorage
    if (CurrentStorage < MinStorage)
    {
        AmountToAdd = 0;
    }
    else if (DesiredStorage < MinStorage)
    {
        // Adjust AmountToAdd to prevent going below MinStorage
        AmountToAdd = MinStorage - CurrentStorage;
    }

    return AmountToAdd;
}

int32 UCpp_Resources::CPPROnDropOffLogic(int32 indexRef)
{
		if (Array[indexRef].DropResource == true)
		{
			return int32(Array[indexRef].CurrentStorage);
		}
		else
		{
			return 0;
		}
}

void UCpp_Resources::ProductionPerTick()
{
	for (int32 i = 0; i < Array.Num(); ++i)
	{
		AddToStorage(i, Array[i].CurrentProduction);
	}
}

int32 UCpp_Resources::SendStorageUpdate(int32 indexRef)
{
    int32 StorageChange;
    // Calculate change in storage from last tick to this tick
    StorageChange = Array[indexRef].CurrentStorage - Array[indexRef].LastTickStorage;
    // Assing LastTickStorage value to be equal to the new storage value
    Array[indexRef].LastTickStorage = Array[indexRef].CurrentStorage;
    
    return StorageChange;
}

int32 UCpp_Resources::SendProductionUpdate(int32 indexRef)
{
    int32 ProductionChange;
    ProductionChange = Array[indexRef].CurrentProduction - Array[indexRef].LastTickProduction;
    Array[indexRef].LastTickProduction = Array[indexRef].CurrentProduction;

    return ProductionChange;
}

bool UCpp_Resources::SetbAccept(int32 indexRef)
{
    Array[indexRef].bAccept = !Array[indexRef].bAccept;
    return Array[indexRef].bAccept;
}
