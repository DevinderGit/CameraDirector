// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBrainComponent.h"





// Sets default values for this component's properties
UCameraBrainComponent::UCameraBrainComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraBrainComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCameraBrainComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UCameraBrainComponent::SetTrackedTargets(AActor* Fighter1, AActor* Fighter2)
{
	FighterA = Fighter1;
	FighterB = Fighter2;
}

void UCameraBrainComponent::SetAnticipatedMoveDirection(const FVector& Direction)
{
	AnticipatedDirection = Direction;
}

FCameraBrainOutput UCameraBrainComponent::GetCurrentCameraTarget() const
{
	return CurrentOutput;
}


void UCameraBrainComponent::UpdateCameraBrain(float DeltaTime)
{
	if (!FighterA || !FighterB) return;

	FVector PosA = FighterA->GetActorLocation();
	FVector PosB = FighterB->GetActorLocation();

	FVector Midpoint = (PosA + PosB) / 2.0f;
	float Distance = FVector::Dist(PosA, PosB);

	// Basic zoom logic: farther apart = zoom out
	float DesiredFOV = FMath::GetMappedRangeValueClamped(FVector2D(300, 1500), FVector2D(60, 90), Distance);

	// Optional anticipation nudge
	FVector AnticipationOffset = AnticipatedDirection * 100.0f; // tweak multiplier

	CurrentOutput.CameraLocation = Midpoint + FVector(-300, 0, 200) + AnticipationOffset; // Over-the-shoulder offset
	CurrentOutput.CameraRotation = (Midpoint - CurrentOutput.CameraLocation).Rotation();
	CurrentOutput.FieldOfView = DesiredFOV;
}
	