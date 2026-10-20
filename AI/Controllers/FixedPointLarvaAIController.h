// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Controllers/FixedPointAIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "FixedPointLarvaAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class AFixedPointCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogFixedPointLarvaAIController, Log, All);

UCLASS()
class FIXEDPOINT_API AFixedPointLarvaAIController
	: public AFixedPointAIController
{
	GENERATED_BODY()

public:

	// LIFECYCLE

	AFixedPointLarvaAIController(const FObjectInitializer& ObjectInitializer);
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	int32 CurrentPatrolPointIndex = INDEX_NONE;

	void SetBlackBoardKeyPatrolLocation(FVector PatrolLocation);

	void ClearBlackBoardKeyPatrolLocation();


protected:

	// PERCEPTION

	UFUNCTION()
	virtual void OnTargetPercieved(AActor* Actor, FAIStimulus Stimulus);

	virtual void OnTargetSightUpdated(AActor* Actor, FAIStimulus SightStimulus);

	virtual void OnTargetSightGained(AFixedPointCharacter* SeenCharacter);

	virtual void OnTargetSightLost(AFixedPointCharacter* LostCharacter);

	UPROPERTY(BlueprintReadOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionComponent> Perception = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig = nullptr;

	// Player characters added when successfully seen.
	UPROPERTY(BlueprintReadOnly, Category = "Perception")
	TArray<AFixedPointCharacter*> PercievedCharacters;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset = nullptr;
};