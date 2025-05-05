// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterTrackerComponent.h"

// Sets default values for this component's properties
UFighterTrackerComponent::UFighterTrackerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFighterTrackerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	UE_LOG(LogTemp, Warning, TEXT("Hello from C++!"));

}


// Called every frame
void UFighterTrackerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// Optional: Debug draw or updates
	if (AreFightersValid())
	{
		FVector Midpoint = GetFighterMidpoint();
		DrawDebugSphere(GetWorld(), Midpoint, 10.0f, 12, FColor::Green, false, 0.1f);

	

	}
}

bool UFighterTrackerComponent::AreFightersValid() const
{
	return IsValid(FighterA) && IsValid(FighterB);
}


FVector UFighterTrackerComponent::GetFighterMidpoint() const
{
	if (!AreFightersValid()) return FVector::ZeroVector;

	return (FighterA->GetActorLocation() + FighterB->GetActorLocation()) / 2.0f;
}

float UFighterTrackerComponent::GetDistanceBetweenFighters() const
{
	if (!AreFightersValid()) return 0.0f;

	return FVector::Dist(FighterA->GetActorLocation(), FighterB->GetActorLocation());

}

EFacingDirection UFighterTrackerComponent::GetFighterFacingDirection(AActor* SourceFighter, AActor* TargetFighter, AActor* CameraActor) const
{
	if (!SourceFighter || !TargetFighter || !CameraActor)
		return EFacingDirection::Unknown;

	FVector SourcePosition = SourceFighter->GetActorLocation();
	FVector TargetPosition = TargetFighter->GetActorLocation();

	// Get Camera's right vector (X-axis on screen)
	FVector CameraRight = CameraActor->GetActorRightVector();
	FVector CameraPosition = CameraActor->GetActorLocation();
	// Vector from Source to Target
	FVector ToTarget = (TargetPosition - SourcePosition).GetSafeNormal();

	// Project ToTarget onto the camera's right axis
	float Dot = FVector::DotProduct(ToTarget, CameraRight);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Dot Product: %f"), Dot));
	//DrawDebugLine(GetWorld(), SourcePosition, SourcePosition + ToTarget * 200.0f, FColor::Blue, false, 2.0f, 0, 2.0f);
	//DrawDebugLine(GetWorld(), CameraPosition, CameraPosition + CameraRight * 200.0f, FColor::Red, false, 2.0f, 0, 2.0f);


	// Dot > 0 = Target is to the right of source (on screen), < 0 = left
	return Dot >= 0.f ? EFacingDirection::Right : EFacingDirection::Left;
}

