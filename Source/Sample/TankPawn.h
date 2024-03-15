// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

UCLASS()
class SAMPLE_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();
	void Move(float throttleSpeed);
	void Sideways(float throttleSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite) UStaticMeshComponent* leftTrack;
	UPROPERTY(BlueprintReadWrite) UStaticMeshComponent* rightTrack;
	UPROPERTY(BlueprintReadWrite) UPrimitiveComponent* tankBody;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	const float TRACK_STRENGTH = 750.0f;
};
