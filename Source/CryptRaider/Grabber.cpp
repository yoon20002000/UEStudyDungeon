// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandler = GetPhysicsHandle();;
	if(PhysicsHandler == nullptr)
	{
		return;
	}

	if(PhysicsHandler->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandler->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());	
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Log, TEXT("Grab Released"));
	UPhysicsHandleComponent* PhysicsHandler = GetPhysicsHandle();
	if(PhysicsHandler == nullptr)
	{
		return;
	}
	
	UPrimitiveComponent* PrimitiveComponent = PhysicsHandler->GetGrabbedComponent();

	if(PrimitiveComponent != nullptr)
	{
		PrimitiveComponent->WakeAllRigidBodies();
		PhysicsHandler->ReleaseComponent();
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandler = GetPhysicsHandle();
	
	if(PhysicsHandler == nullptr)
	{
		return;
	}
	
	const FVector Start = GetComponentLocation();
	const FVector End = Start + GetForwardVector() * MaxGrabDistance;
	UWorld* World = GetWorld();
	DrawDebugLine(World, Start, End, FColor::Red);
	DrawDebugSphere(World,End,10,10,FColor::Blue, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	bool IsHit = World->SweepSingleByChannel(
		HitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);

	if(IsHit)
	{
		DrawDebugSphere(World,HitResult.Location,10,10,FColor::Red, false, 5);
		DrawDebugSphere(World,HitResult.ImpactPoint,10,10,FColor::Yellow, false, 5);
		UPrimitiveComponent* PrimitiveComponent =  HitResult.GetComponent();
		
		PhysicsHandler->GrabComponentAtLocationWithRotation(
			PrimitiveComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation());
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandler == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandler is nullptr!!!"));
	}
	
	return PhysicsHandler;
}

