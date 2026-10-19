// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "../../Player/Characters/FixedPointCharacter.h"
#include "BehaviorTree/BlackBoardComponent.h"

DEFINE_LOG_CATEGORY(LogFixedPointAIController);

// LIFECYLE
AFixedPointAIController::AFixedPointAIController(const FObjectInitializer& ObjectInitializer)
{
	//Create The perception component in memory and assign to are variable upon construction
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	SetPerceptionComponent(*PerceptionComponent);

	//create the sight configuration in memory
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));

	//Set the default values for sight here 

	SightConfig->SightRadius = 3000.f;

	SightConfig->LoseSightRadius = 3500.f;

	SightConfig->PeripheralVisionAngleDegrees = 90.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;

	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	// OTHER SETTABLE SIGHT CONFIG VALUES EXIST IF NEEDED 

	// Set up the sight config we have made
	GetAIPerceptionComponent()->ConfigureSense(*SightConfig);

	GetAIPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());

	// sets the AI controllers team as 2 
	SetGenericTeamId(FGenericTeamId(2));

	

}

void AFixedPointAIController::BeginPlay()
{
	Super::BeginPlay();

	//bind the function we call we call when perception gets updated.
	GetAIPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AFixedPointAIController::OnTargetPercieved);

	UE_LOG(LogFixedPointAIController, Log, TEXT("BeginPlay() | Binded Function of on target percieved to Delegate OnTargetPerceptionUpdated"))


}

void AFixedPointAIController::Tick(float DeltaTime)
{

}

//PERCEPTION

// What Happens when the AI percieves an actor through any sense
void AFixedPointAIController::OnTargetPercieved(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogFixedPointAIController, Log, TEXT("OnTargetPercieved() | Function called"))

	if (Stimulus.Type == SightConfig->GetSenseID())
	{
		OnTargetSighted(Actor, Stimulus);
	}
}

// what happens when the AI has seen a player through sight sense
void AFixedPointAIController::OnTargetSighted(AActor* Actor, FAIStimulus SightStimulus)
{
	// The Player The AI has just Seen
	AFixedPointCharacter* PerceivedCharacter = Cast<AFixedPointCharacter>(Actor);

	// if the actor we saw was not a Player 
	if (!IsValid(PerceivedCharacter))
	{
		UE_LOG(LogFixedPointAIController, Warning, TEXT("OnTargetSighted() | The Actor seen with sight sense was not a AFixedPointCharacter"))
			return;
	}

	// if we did not succesfully see the AI player meaning collision checks and so on 
	if (!SightStimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogFixedPointAIController, Warning, TEXT("OnTargetSighted() | The Sight Stimulus was not Successfully sensed"))
			return;
	}

	PercievedCharacters.AddUnique(PerceivedCharacter);

	UE_LOG(LogFixedPointAIController, Log, TEXT("OnTargetSighted() | Added this percieved character to the Array of percieved characters"))



	// If the AI actually sees the actor
	//SightStimulus.WasSuccessfullySensed
}