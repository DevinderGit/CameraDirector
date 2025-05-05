// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FighterTrackerComponent.generated.h"




UENUM(BlueprintType)
enum class EFacingDirection : uint8
{
	Left     UMETA(DisplayName = "Left"),
	Right    UMETA(DisplayName = "Right"),
	Forward  UMETA(DisplayName = "Forward"),
	Unknown  UMETA(DisplayName = "Unknown")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class FIGHTCAMERAPLUGIN_API UFighterTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFighterTrackerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Fighter references
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter Tracking")
	AActor* FighterA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter Tracking")
	AActor* FighterB;

	UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = "Fighter Tracking")
	AActor* ActiveCamera;

	// Midpoint between fighters
	UFUNCTION(BlueprintCallable, Category = "Fighter Tracking")
	FVector GetFighterMidpoint() const;

	// Distance between fighters
	UFUNCTION(BlueprintCallable, Category = "Fighter Tracking")
	float GetDistanceBetweenFighters() const;

	// Check if both fighters are valid
	UFUNCTION(BlueprintCallable, Category = "Fighter Tracking")
	bool AreFightersValid() const;
		

	// Facing Position for both fighters
	UFUNCTION(BlueprintCallable, Category = "Fighter Tracking")
	EFacingDirection GetFighterFacingDirection(AActor* SourceFighter, AActor* TargetFighter, AActor* CameraActor)  const;



};

