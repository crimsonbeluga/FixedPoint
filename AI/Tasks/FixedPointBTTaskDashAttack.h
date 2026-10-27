// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FixedPointBTTaskDashAttack.generated.h"	

struct FTimerHandle;
/**
 * 
 */

class AFixedPointCharacter;
class AFixedPointLarvaAIController;
class AFixedPointLarvaCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogFixedPointBTTaskDashAttack, Log, All);

UCLASS()
class FIXEDPOINT_API UFixedPointBTTaskDashAttack : public UBTTaskNode
{
	GENERATED_BODY()
	

public:

UFixedPointBTTaskDashAttack(const FObjectInitializer& ObjectInitializer);

protected:



	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual EBTNodeResult::Type AbortTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;


	void UpdateDashMovement(float DeltaSeconds);

	bool HasDashStalled();

	bool canGetStunned = false;

	AFixedPointLarvaCharacter* LarvaCharacter = nullptr;

	AFixedPointLarvaAIController* LarvaAIController = nullptr;

	UBlackboardComponent* BB = nullptr;

	AFixedPointCharacter* TargetActor = nullptr;

	FTimerHandle DashStunBufferTimer;

	FRotator DashRotation = FRotator::ZeroRotator;
};
