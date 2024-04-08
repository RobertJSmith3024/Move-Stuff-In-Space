// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveStuffInSpace/Cpp_Upgrades/Cpp_Upgrade_Storage.h"
#include "MoveStuffInSpace/Cpp_Resources.h"

void UCpp_Upgrade_Storage::Upgrade(class UCpp_Resources* ResourceClass)
{
	int32 ArrayElements = ResourceClass->Array.Num();
	for (int32 i = 0; i < ArrayElements; i++)
	{
		ResourceClass->Array[i].MaxStorage += StorageIncrement;
	}

	Cost *= 1.4;
	Level += 1;
}
