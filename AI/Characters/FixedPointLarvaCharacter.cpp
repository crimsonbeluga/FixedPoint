// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointLarvaCharacter.h"
#include "../Controllers/FixedPointLarvaAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

AFixedPointLarvaCharacter::AFixedPointLarvaCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	// Static class returns a pointer to the UClass of AFixedPointAIController which we then set as the inherited variable of AI controller class
	// this being the class that controls this character
	AIControllerClass = AFixedPointLarvaAIController::StaticClass();

	// Automatically spawn and possess with an AI Controller.
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetMesh()->SetRelativeLocation(FVector(-3.5f, 0.f, -40.f));

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetMesh()->SetRelativeScale3D(FVector(.35f, .35f, .35f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(40.f);
	GetCapsuleComponent()->SetCapsuleRadius(40.f);



	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = (FRotator(0.000000f, 180.000000f, 0.000000f));
		
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

void AFixedPointLarvaCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (MovementState == EMovementState::Patrol)
	{
		GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;



	}



   
}

void AFixedPointLarvaCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFixedPointLarvaCharacter, MovementState);
}

 void AFixedPointLarvaCharacter::OnRep_MovementState()
 {
	 switch (MovementState)
	 {
	 case EMovementState::Patrol:
		 GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
		 break;

	 case EMovementState::Roar:
		 GetCharacterMovement()->MaxWalkSpeed = RoarSpeed;
		 break;

	 case EMovementState::Dash:
		 GetCharacterMovement()->MaxWalkSpeed = DashSpeed;
		 break;

	 case EMovementState::Stun:
		 GetCharacterMovement()->MaxWalkSpeed = StunSpeed;
		 break;
	 }

	 OnMovementStateChanged.Broadcast(MovementState);
 }

void AFixedPointLarvaCharacter::SetMovementState(EMovementState NewState)
{
	const bool bStateChanged = MovementState != NewState;

	if(!bStateChanged)
	{
		return;
	}

	MovementState = NewState;


	switch (MovementState)
	{
	case EMovementState::Patrol:


		GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;

		break;

	case EMovementState::Roar:

		GetCharacterMovement()->MaxWalkSpeed = RoarSpeed;

		break;

	case EMovementState::Dash:
		
		GetCharacterMovement()->MaxWalkSpeed = DashSpeed;

		break;

	case EMovementState::Stun:
		
		GetCharacterMovement()->MaxWalkSpeed = StunSpeed;

		break;
	}


	OnMovementStateChanged.Broadcast(MovementState);
}
