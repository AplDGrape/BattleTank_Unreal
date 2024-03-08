// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "DrawDebugHelpers.h"

#define out

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	UInputComponent* inputComponent = this->FindComponentByClass<UInputComponent>();
	inputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &ATankController::OnFire);
}

void ATankController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

bool ATankController::GetRayHitLocation()
{
	bool hasHit = this->DeprojectScreenPositionToWorld(this->crosshairScreenLoc.X, this->crosshairScreenLoc.Y, out this->latestCameraLoc, out this->latestWorldDirection);
	return hasHit;
}

//perform ray tracing and hits the first valid object
bool ATankController::GetWorldPoint()
{
	FHitResult hitResult;
	FVector startLoc = this->latestCameraLoc; //Alt: PlayerCameraManager->GetCameraLocation();
	FVector endLoc = startLoc + (this->latestWorldDirection * 50000000.0f);

	bool result = this->GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECollisionChannel::ECC_Visibility);
	//DrawDebugLine(this-GetWorld(), startLoc, endLoc, FColor::Red, false, 5.0, 0, 5.0f);
	this->latestWorldPoint = hitResult.Location;
	this->latestWorldPoint.Z += 100.0f; //add offset
	return result;
}

void ATankController::OnFire()
{
	bool hasHit = this->GetRayHitLocation();

	if (hasHit) {
		UE_LOG(LogTemp, Display, TEXT("Crosshair screen location: %s"), *this->crosshairScreenLoc.ToString());

		if (this->GetWorldPoint()) {
			UE_LOG(LogTemp, Display, TEXT("Firing on: %s"), *this->latestWorldPoint.ToString());
		}
	
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No available target!"));
	}
}
