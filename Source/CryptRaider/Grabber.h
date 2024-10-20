// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400.0f;
	UPROPERTY(EditAnywhere)
	float GrabRadius = 100.0f;
	UPROPERTY(EditAnywhere)
	float HoldDistance = 200.0f;

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void Release();
	UFUNCTION(BlueprintCallable)
	void Grab();
	UPhysicsHandleComponent* GetPhysicsHandle() const;

private:
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
};
