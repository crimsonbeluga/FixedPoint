// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointAICharacter.h"
#include "../Controllers/FixedPointAIController.h"

// Sets default values
AFixedPointAICharacter::AFixedPointAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static class returns a pointer to the UClass of AFixedPointAIController which we then set as the inherited variable of AI controller class
	// this being the class that controls this character
	AIControllerClass = AFixedPointAIController::StaticClass();

	// Automatically spawn and possess with an AI Controller.
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


}

// Called when the game starts or when spawned
void AFixedPointAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFixedPointAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFixedPointAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

