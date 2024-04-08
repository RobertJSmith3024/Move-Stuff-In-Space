// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Planet_Home.h"
#include "Cpp_Resources.h"

ACpp_Planet_Home::ACpp_Planet_Home()
{
}

void ACpp_Planet_Home::BeginPlay()
{
	Super::BeginPlay();
}

void ACpp_Planet_Home::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACpp_Planet_Home::CreateBaseResourceProduction(UCpp_Resources* ResourcesToSet)
{
	for (int32 i = 0; i < ResourcesToSet->Array.Num(); ++i)
	{
		ResourcesToSet->Array[i].BaseProduction = BaseProduction;
	}
}

