// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FixedPointAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
struct FAIStimulus;
class AFixedPointCharacter;
/**
 *
 */

DECLARE_LOG_CATEGORY_EXTERN(LogFixedPointAIController, Log, All);

UCLASS()
class FIXEDPOINT_API AFixedPointAIController : public AAIController
{
	GENERATED_BODY()

public:

	//LIFECYCLE

	AFixedPointAIController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//PERCEPTION

protected:

	//LIFECYCLE

	//PERCEPTION

	UFUNCTION()
	virtual void OnTargetPercieved(AActor* Actor, FAIStimulus Stimulus);

	virtual void OnTargetSighted(AActor* Actor, FAIStimulus SightStimulus);



	UPROPERTY(BlueprintReadOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionComponent> Perception = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig = nullptr;

	// The Players The AI Can Currently See
	UPROPERTY(BlueprintReadOnly, Category = "Perception")
	TArray<AFixedPointCharacter*> PercievedCharacters;




private:

	//LIFECYCLE

	

	//PERCEPTION

};