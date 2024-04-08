// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cpp_Upgrade.h"
#include "Cpp_Upgrade_Upkeep.generated.h"

/**
 * 
 */
UCLASS()
class MOVESTUFFINSPACE_API UCpp_Upgrade_Upkeep : public UCpp_Upgrade
{
	GENERATED_BODY()
	
public:
	virtual void Upgrade(class UCpp_Resources* ResourceClass) override;

protected:

private:

};
