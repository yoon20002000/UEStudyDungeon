// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetOwner()->GetActorLocation();
	
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* Owner = GetOwner();

	FVector TargetLocation = StartLocation;
	if(IsSwitchOn == true)
	{
		TargetLocation += MoveOffset;
	}
	FVector Location = Owner->GetActorLocation();
	float Speed = MoveOffset.Length()/ MoveTime;
	FVector NewLocation = FMath::VInterpConstantTo(Location, TargetLocation, DeltaTime, Speed);
	Owner->SetActorLocation(NewLocation);
}

void UMover::SetMove(const bool InIsSwitchOn)
{
	if(IsSwitchOn == InIsSwitchOn)
	{
		return;
	}
	IsSwitchOn = InIsSwitchOn;
}

