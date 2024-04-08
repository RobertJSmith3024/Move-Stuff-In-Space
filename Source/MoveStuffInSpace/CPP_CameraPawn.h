// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "CPP_CameraPawn.generated.h"

UCLASS()
class MOVESTUFFINSPACE_API ACPP_CameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_CameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	int32 Gold;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Resource storing logic
	UFUNCTION(BlueprintCallable)
	void AddToStoragePool(class UCpp_Resources* ResourcesToSet, int32 indexRef, int32 storageUpdate);

	// Resource storing logic
	UFUNCTION(BlueprintCallable)
	void AddToCurrentProduction(class UCpp_Resources* ResourcesToSet, int32 indexRef, int32 productionUpdate);

	UFUNCTION(BlueprintCallable)
	int32 GetGold();
	UFUNCTION(BlueprintCallable)
	void SetGold(int32 newGold);

	UFUNCTION(BlueprintCallable)
	static float CalculateCameraBoomLength(float FOVDegrees, float AspectRatio, float TargetExtent, bool IsHorizontalScreen);


private:
	/** Collision Sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionComponent;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Declare an instance of your actor component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Resources, meta = (AllowPrivateAccess = "true"))
	class UCpp_Resources* ResourceComponent;

	///////////////////////////////////////////////////////
	// Blueprint UI
	// Reference to the Widget Blueprint class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PlanetWidgetBlueprintClass;	   
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ShipWidgetBlueprintClass;		   
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> UpgradeWidgetWidgetBlueprintClass;

	/** Camera boom and camera setup */
	void SetUpCamera();
	// Function to open Widget
	UFUNCTION(BlueprintCallable, Category = "UI")
	void OpenWidget(TSubclassOf<UUserWidget> Widget);

};
