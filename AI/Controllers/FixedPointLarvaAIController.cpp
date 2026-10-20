// Fill out your copyright notice in the Description page of Project Settings.

#include "FixedPointLarvaAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "../../Player/Characters/FixedPointCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

DEFINE_LOG_CATEGORY(LogFixedPointLarvaAIController);

// LIFECYCLE

AFixedPointLarvaAIController::AFixedPointLarvaAIController(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create the perception component and store it in our variable.
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(
		TEXT("PerceptionComponent"));

	// Register it as this controller's perception component.
	SetPerceptionComponent(*Perception);

	// Create the sight configuration.
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(
		TEXT("Sight Configuration"));

	// Set the default sight values.
	SightConfig->SightRadius = 3000.f;
	SightConfig->LoseSightRadius = 3500.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	// Apply the sight configuration.
	Perception->ConfigureSense(*SightConfig);

	Perception->SetDominantSense(
		SightConfig->GetSenseImplementation());

	// Set this controller's team to 2.
	SetGenericTeamId(FGenericTeamId(2));
}

void AFixedPointLarvaAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!IsValid(BehaviorTreeAsset.Get()))
	{
		UE_LOG(
			LogFixedPointLarvaAIController,
			Warning,
			TEXT("OnPossess() | No Behavior Tree asset assigned"));

		return;
	}

	if (!RunBehaviorTree(BehaviorTreeAsset.Get()))
	{
		UE_LOG(
			LogFixedPointLarvaAIController,
			Error,
			TEXT("OnPossess() | Failed to start Behavior Tree"));

		return;
	}

	UE_LOG(
		LogFixedPointLarvaAIController,
		Log,
		TEXT("OnPossess() | Behavior Tree started"));
}

void AFixedPointLarvaAIController::BeginPlay()
{
	Super::BeginPlay();

	// Call OnTargetPercieved whenever a target's perception changes.
	Perception->OnTargetPerceptionUpdated.AddDynamic(
		this,
		&AFixedPointLarvaAIController::OnTargetPercieved);

}

void AFixedPointLarvaAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// PERCEPTION

// Called when perception of an actor changes through any sense.
void AFixedPointLarvaAIController::OnTargetPercieved(AActor* Actor, FAIStimulus Stimulus)
{
	// Forward sight updates to our sight-specific function.
	if (Stimulus.Type == SightConfig->GetSenseID())
	{
		OnTargetSightUpdated(Actor, Stimulus);
	}
}

// Handles perception updates from the sight sense
void AFixedPointLarvaAIController::OnTargetSightUpdated(AActor* Actor, FAIStimulus SightStimulus)
{
	// Attempt to treat the perceived actor as a player character.
	AFixedPointCharacter* PerceivedCharacter =
		Cast<AFixedPointCharacter>(Actor);

	if (!IsValid(PerceivedCharacter))
	{
		UE_LOG(
			LogFixedPointLarvaAIController,
			Warning,
			TEXT("OnTargetSighted() | The actor was not an AFixedPointCharacter"));

		return;
	}

	// if we have gained sight on a player do this
	if (SightStimulus.WasSuccessfullySensed())
	{
		OnTargetSightGained(PerceivedCharacter);
	}
	// if we have lost sight of a player do this
	else
	{
		OnTargetSightLost(PerceivedCharacter);
	}

	


}

void AFixedPointLarvaAIController::OnTargetSightGained(AFixedPointCharacter* SeenCharacter)
{
	// QUESTION THIS VALIDITY CHECK IF ANY ISSUES ARRIVE WHY DOES IT MATTER IF WHAT THE AI HAS JUST SEEN WAS NOT VALID?
	if (!IsValid(SeenCharacter))
	{
		UE_LOG(LogFixedPointLarvaAIController, Warning, TEXT("OnTargetSightGained () | The Player we have sighted is not valid"));
		return;
	}

	// add the seen player to the array of players ar AI is currently percieving
	PercievedCharacters.AddUnique(SeenCharacter);


	UE_LOG(
		LogFixedPointLarvaAIController, Log, TEXT("OnTargetSighted() | Added perceived character to PercievedCharacters"));


}

void AFixedPointLarvaAIController::OnTargetSightLost(AFixedPointCharacter* LostCharacter)
{
	// QUESTION THIS VALIDITY CHECK IF ANY ISSUES ARRIVE WHY DOES IT MATTER IF WHAT THE AI LOST SIGHT OF WAS NOT VALID?
	if (!IsValid(LostCharacter))
	{
		UE_LOG(LogFixedPointLarvaAIController, Warning, TEXT("OnTargetSightLost () | The Player we lost sight of is not valid"));
		return;
	}

	// Remove the player the AI lost sight of from the array of players are AI is currently percieving
	PercievedCharacters.Remove(LostCharacter);


	UE_LOG(LogFixedPointLarvaAIController, Log, TEXT("OnTargetSightLost() | Removed perceived character from PercievedCharacters"));

}

void AFixedPointLarvaAIController::SetBlackBoardKeyPatrolLocation(FVector PatrolLocation)
{
	UBlackboardComponent* BB = GetBlackboardComponent();

	if (!IsValid(BB))
	{
		UE_LOG(LogFixedPointLarvaAIController, Warning, TEXT("SetBlackBoardKeyPatrolLocation() | Black Board Component Is Not Valid"));

		return;
	}

	BB->SetValueAsVector(TEXT("PatrolLocation"), PatrolLocation);

	UE_LOG(LogFixedPointLarvaAIController, Log,TEXT("SetBlackBoardKeyPatrolLocation() | Black Board Key Patrol Location Has Been Set: %s")
		,*PatrolLocation.ToString());
}

void AFixedPointLarvaAIController::ClearBlackBoardKeyPatrolLocation()
{
	UBlackboardComponent* BB = GetBlackboardComponent();

	if (!IsValid(BB))
	{
		UE_LOG(LogFixedPointLarvaAIController, Warning, TEXT("ClearBlackBoardKeyPatrolLocation() | Black Board Component Is Not Valid"));

		return;
	}

	BB->ClearValue(TEXT("PatrolLocation"));

	UE_LOG(LogFixedPointLarvaAIController, Log, TEXT("ClearBlackBoardKeyPatrolLocation() | Black Board Key Patrol Location Has Been Cleared"));
}