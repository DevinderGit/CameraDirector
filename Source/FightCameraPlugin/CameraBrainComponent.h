// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraBrainComponent.generated.h"


USTRUCT(BlueprintType)
struct FCameraBrainOutput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector CameraLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator CameraRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FieldOfView;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTCAMERAPLUGIN_API UCameraBrainComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraBrainComponent();


	void SetTrackedTargets(AActor* Fighter1, AActor* Fighter2);
	void SetAnticipatedMoveDirection(const FVector& Direction); // From AnticipationEngine

	FCameraBrainOutput GetCurrentCameraTarget() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* FighterA;
	AActor* FighterB;

	FVector AnticipatedDirection;

	FCameraBrainOutput CurrentOutput;

	void UpdateCameraBrain(float DeltaTime);
	
};
