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
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (const AActor* Actor : Actors)
	{
		if(Actor->ActorHasTag(UnlockTag))
		{
			UE_LOG(LogTemp, Log, TEXT("Unlocking Key"));
		}
	}
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
