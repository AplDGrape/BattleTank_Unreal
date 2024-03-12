// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define out

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	//Hides the actor
	if (this->actorCopy != nullptr) {
		this->actorCopy->SetActorHiddenInGame(true);
	}

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

		if (this->actorCopy != nullptr && this->GetWorldPoint()) {
			FActorSpawnParameters spawnParams;
			spawnParams.Template = this->actorCopy;
			spawnParams.Owner = this->GetOwner();

			AActor* myActor = this->GetWorld()->SpawnActor<AActor>(this->actorCopy->GetClass(), spawnParams);
			myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform); //works but does not show hierarchy in outliner during gameplay
			myActor->SetActorHiddenInGame(false);
			myActor->SetActorLocation(this->latestWorldPoint);
			myActor->SetActorRotation(this->actorCopy->GetActorRotation());

			UE_LOG(LogTemp, Display, TEXT("Firing on: %s"), *this->latestWorldPoint.ToString());
		}
	
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No available target!"));
	}
}
