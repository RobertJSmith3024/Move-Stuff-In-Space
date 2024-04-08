// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Upgrade_Production.h"
#include "MoveStuffInSpace/Cpp_Resources.h"

void UCpp_Upgrade_Production::Upgrade(UCpp_Resources* ResourceClass)
{
	int32 ArrayElements = ResourceClass->Array.Num();
	for (int32 i = 0; i < ArrayElements; i++)
	{
		if (ResourceClass->Array[i].CurrentProduction > 0)
		{
			ResourceClass->Array[i].CurrentProduction += ProductionIncrement;
		}
	}

	Cost *= 1.4;
	Level += 1;
}
