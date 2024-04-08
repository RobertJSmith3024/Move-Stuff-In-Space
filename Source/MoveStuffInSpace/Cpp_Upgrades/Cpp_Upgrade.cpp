// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Upgrade.h"
#include "MoveStuffInSpace/Cpp_Resources.h"

int32 UCpp_Upgrade::GetCost()
{
	return Cost;
}

void UCpp_Upgrade::SetCost(int32 newCost)
{
	Cost = newCost;
}

int32 UCpp_Upgrade::GetLevel()
{
	return Level;
}

void UCpp_Upgrade::SetLevel(int32 newLevel)
{
	Level = newLevel;
}

FName UCpp_Upgrade::GetName()
{
	return Name;
}

void UCpp_Upgrade::SetName(FName newName)
{
	Name = newName;
}

void UCpp_Upgrade::Upgrade(UCpp_Resources* ResourceClass)
{

}


