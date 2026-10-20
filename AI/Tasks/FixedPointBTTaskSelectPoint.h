// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FixedPointBTTaskSelectPoint.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFixedPointBTTaskSelectPoint, Log, All);

/**
 * 
 */

class AFixedPointLarvaCharacter;
class AFixedPointLarvaAIController;
class AFixedPointPatrolPoint;

UCLASS()
class FIXEDPOINT_API UFixedPointBTTaskSelectPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory) override;

protected: 

	AFixedPointPatrolPoint* SelectNextPatrolPoint(const TArray<TObjectPtr<AFixedPointPatrolPoint>>&);

	AFixedPointLarvaCharacter* LarvaCharacter = nullptr;

	AFixedPointLarvaAIController* LarvaController = nullptr;


};
