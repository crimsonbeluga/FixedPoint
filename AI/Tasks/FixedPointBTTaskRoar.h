// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FixedPointBTTaskRoar.generated.h"

/**
 * 
 */						
DECLARE_LOG_CATEGORY_EXTERN(LogFixedPointBTTaskRoar, Log, All);

class AFixedPointLarvaAIController;
class AFixedPointLarvaCharacter;


UCLASS()
class FIXEDPOINT_API UFixedPointBTTaskRoar : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:


	AFixedPointLarvaCharacter* LarvaCharacter = nullptr;

	AFixedPointLarvaAIController* LarvaAIController = nullptr;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
