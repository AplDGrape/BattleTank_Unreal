// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	//Called when game starts
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	UPROPERTY(BlueprintReadWrite) FVector2D crosshairScreenLoc;
	UPROPERTY(BlueprintReadWrite) AActor* actorCopy;

private:
	FVector latestCameraLoc;
	FVector latestWorldDirection;
	FVector latestWorldPoint;

	bool GetRayHitLocation();
	bool GetWorldPoint();
	void OnFire();

	void OnMove(float axis);
	void OnSideways(float axis);
};
