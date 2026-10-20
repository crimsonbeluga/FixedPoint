// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointLarvaCharacter.h"
#include "AI/Controllers/FixedPointLarvaAIController.h"

AFixedPointLarvaCharacter::AFixedPointLarvaCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static class returns a pointer to the UClass of AFixedPointAIController which we then set as the inherited variable of AI controller class
	// this being the class that controls this character
	AIControllerClass = AFixedPointLarvaAIController::StaticClass();

	// Automatically spawn and possess with an AI Controller.
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


}