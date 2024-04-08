// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_BattleRoyaleZone.h"
#include "Components/SphereComponent.h"

// Sets default values
ACpp_BattleRoyaleZone::ACpp_BattleRoyaleZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(SceneComponent);
	
	CylinderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	CylinderMesh->SetupAttachment(SceneComponent);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	//if (CylinderAsset.Succeeded())
	//{
	//	CylinderMesh->SetStaticMesh(CylinderAsset.Object);
	//	CylinderMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//	CylinderMesh->SetWorldScale3D(FVector(1.0f));
	//}
}

// Called when the game starts or when spawned
void ACpp_BattleRoyaleZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACpp_BattleRoyaleZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACpp_BattleRoyaleZone::SetupSphereRadius(float NewRadius)
{
	// Set the cylinder mesh size 
	// Calculate the scale factor based on the desired radius and the original mesh size
	FVector OriginalMeshSize = CylinderMesh->GetStaticMesh()->GetBounds().BoxExtent;
	// Add some buffer to radius (Planet radius:300 + hollow cylinder thickness: 100)
	float RequiredRadius = NewRadius + 400.f;
	float ScaleFactor = RequiredRadius / OriginalMeshSize.X;

	// Apply the scale factor uniformly to all three axes
	FVector NewScale = FVector(1) * ScaleFactor;
	CylinderMesh->SetWorldScale3D(FVector(NewScale.X, NewScale.Y, 100));

	// Set the sphere collision radius
	SphereCollision->SetSphereRadius(NewRadius);
}

