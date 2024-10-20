// Fill out your copyright notice in the Description page of Project Settings.


#include "CryptRaider/Public/TriggerComponent.h"

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Success"));
}
