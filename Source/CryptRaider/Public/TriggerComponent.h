// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "CryptRaider/Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName UnlockTag = FName("Unlock1");
	UPROPERTY(EditAnywhere)
	FName GrabbedTag = FName("Grabbed");
	TObjectPtr<UMover> Mover;
public:
	UTriggerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* InMover);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	AActor* GetAcceptableActor() const;
};
