// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "CPP_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Cpp_Resources.h"

// Sets default values
ACPP_CameraPawn::ACPP_CameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetUpCamera();

	// Create an instance of your actor component
	ResourceComponent = CreateDefaultSubobject<UCpp_Resources>(TEXT("YourActorComponent"));
}

// Called when the game starts or when spawned
void ACPP_CameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_CameraPawn::AddToStoragePool(UCpp_Resources* ResourcesToSet, int32 indexRef, int32 storageUpdate)
{
	ResourcesToSet->Array[indexRef].CurrentStorage += storageUpdate;
}

void ACPP_CameraPawn::AddToCurrentProduction(UCpp_Resources* ResourcesToSet, int32 indexRef, int32 productionUpdate)
{
	ResourcesToSet->Array[indexRef].CurrentProduction += productionUpdate;
}

int32 ACPP_CameraPawn::GetGold()
{
	return Gold;
}

void ACPP_CameraPawn::SetGold(int32 newGold)
{
	Gold = newGold;
}

float ACPP_CameraPawn::CalculateCameraBoomLength(float FOVDegrees, float AspectRatio, float TargetExtent, bool IsHorizontalScreen)
{
	float CameraBoomLength;
	if (IsHorizontalScreen)
	{
		float TanRatio = FMath::Tan(FMath::DegreesToRadians(FOVDegrees / 2));
		float VerticalFOV = 2 * FMath::Atan(1 / AspectRatio * TanRatio);
		CameraBoomLength = TargetExtent / FMath::Tan(VerticalFOV / 2);
	}
	else
	{
		CameraBoomLength = TargetExtent / FMath::Tan(FMath::DegreesToRadians(FOVDegrees / 2));
	}
	return CameraBoomLength;
}

void ACPP_CameraPawn::SetUpCamera()
{
	// Create a collision shpere
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(CollisionComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ACPP_CameraPawn::OpenWidget(TSubclassOf<UUserWidget> Widget)
{
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACPP_CameraPawn::OpenWidget(): Widget is InValid"));
		return;
	}
	//Get the player controller
	auto* PlayerController = GetWorld()->GetFirstPlayerController();

	// Check if the Widget Blueprint Class is set
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACPP_CameraPawn::OpenWidget(): PlayerController is InValid"));
		return;
	}

	// Create the widget
	UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(PlayerController, Widget);
	if (!WidgetInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACPP_CameraPawn::OpenWidget(): WidgetInstance is InValid"));
		return;
	}

	// Add the widget to the viewport
	WidgetInstance->AddToViewport();

}

