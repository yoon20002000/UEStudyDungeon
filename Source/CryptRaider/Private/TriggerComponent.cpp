// Fill out your copyright notice in the Description page of Project Settings.


#include "CryptRaider/Public/TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* AcceptableActor = GetAcceptableActor();
	// Unlock
	if (AcceptableActor != nullptr)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(AcceptableActor->GetRootComponent());
		if (PrimitiveComponent != nullptr)
		{
			PrimitiveComponent->SetSimulatePhysics(false);
		}
		AcceptableActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);;
		Mover->SetMove(true);
	}
	// Lock
	else
	{
		Mover->SetMove(false);
	}
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (AActor* Actor : Actors)
	{
		const bool IsHasUnlock = Actor->ActorHasTag(UnlockTag);
		const bool IsGrabbed = Actor->ActorHasTag(GrabbedTag);
		if (IsHasUnlock == true && IsGrabbed == false)
		{
			return Actor;
		}
	}
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* InMover)
{
	Mover = InMover;
}
