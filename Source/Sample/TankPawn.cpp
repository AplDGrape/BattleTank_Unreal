// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATankPawn::Move(float throttleSpeed)
{
	float speed = this->tankBody->GetMass() * this->TRACK_STRENGTH;
	FVector forceVector = this->GetActorForwardVector() * throttleSpeed * speed;
	FVector lTrackLoc = this->leftTrack->GetComponentLocation();
	FVector rTrackLoc = this->rightTrack->GetComponentLocation();

	this->tankBody->AddForceAtLocation(forceVector, lTrackLoc);
	this->tankBody->AddForceAtLocation(forceVector, rTrackLoc);
	UE_LOG(LogTemp, Display, TEXT("Attempting to move with vector %s, Speed of %f"), *forceVector.ToString(), (throttleSpeed * speed));

}

void ATankPawn::Sideways(float throttleSpeed)
{
	float speed = (this->tankBody->GetMass() * this->TRACK_STRENGTH) * 0.4f; //damp sideways speed
	FVector forceVector = this->GetActorForwardVector() * throttleSpeed * speed;
	FVector lTrackLoc = this->leftTrack->GetComponentLocation();
	FVector rTrackLoc = this->rightTrack->GetComponentLocation();

	this->tankBody->AddForceAtLocation(forceVector, lTrackLoc);
	this->tankBody->AddForceAtLocation(forceVector, -rTrackLoc);
	UE_LOG(LogTemp, Display, TEXT("Attempting to sideways with vector %s, Speed of %f"), *forceVector.ToString(), (throttleSpeed * speed));
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

