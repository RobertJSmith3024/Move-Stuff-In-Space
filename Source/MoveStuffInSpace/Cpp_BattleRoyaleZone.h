// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_BattleRoyaleZone.generated.h"

UCLASS()
class MOVESTUFFINSPACE_API ACpp_BattleRoyaleZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_BattleRoyaleZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetupSphereRadius(float NewRadius);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere", meta = (AllowPrivateAccess = true))
	class USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere", meta = (AllowPrivateAccess = true))
	class USphereComponent* SphereCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* CylinderMesh;

};
