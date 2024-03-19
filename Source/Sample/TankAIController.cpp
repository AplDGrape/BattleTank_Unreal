// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "DrawDebugHelpers.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATankPawn* myPawn = this->GetControlledTank();
	ATankPawn* myPlayer = this->GetPlayerTank();

	if (myPlayer != nullptr && myPawn != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("AI %s found player %s"), *myPawn->GetName(), *myPlayer->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Enemy tank or player tank is not assigned. Cancelling AI controller."));
	}
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	this->fireTicks += deltaTime;
	if (this->fireTicks > this->FIRE_INTERVAL) {
		this->FIRE_INTERVAL = FMath::FRandRange(0.25, 4.0f);
		this->fireTicks = 0.0f;
		this->OnFire();
	}
}

ATankPawn* ATankAIController::GetControlledTank() const
{
	return this->GetPawn<ATankPawn>();
}

ATankPawn* ATankAIController::GetPlayerTank() const
{
	ATankPawn* playerPawn = this->GetWorld()->GetFirstPlayerController()->GetPawn<ATankPawn>();
	return playerPawn;
}

bool ATankAIController::GetWorldPoint()
{
	FHitResult hitResult;
	FVector startLoc = this->GetControlledTank()->GetActorLocation();
	FVector endLoc = this->GetPlayerTank()->GetActorLocation();

	bool result = this->GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECollisionChannel::ECC_WorldDynamic);
	DrawDebugLine(this->GetWorld(), startLoc, endLoc, FColor::Blue, false, 1.0, 0, 5.0f);
	//this->latestWorldPoint = hitResult.Location;

	this->latestWorldPoint = endLoc;

	return result;
}

void ATankAIController::OnFire()
{
	if (this->actorCopy != nullptr && this->GetWorldPoint()) {
		FActorSpawnParameters spawnParams;
		spawnParams.Template = this->actorCopy;
		spawnParams.Owner = this->GetOwner();

		AActor* myActor = this->GetWorld()->SpawnActor<AActor>(this->actorCopy->GetClass(), spawnParams);
		myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
		myActor->SetActorHiddenInGame(false);
		myActor->SetActorLocation(this->latestWorldPoint);
		myActor->SetActorRotation(this->actorCopy->GetActorRotation());

		UE_LOG(LogTemp, Display, TEXT("Firing on: %s"), *this->latestWorldPoint.ToString());
	}
}



