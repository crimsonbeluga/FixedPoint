// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LarvaWallImpactStun.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogBTTaskLarvaWallImpactStun, Log, All);

class AFixedPointLarvaAIController;
class AFixedPointLarvaCharacter;
class AFixedPointCharacter;

struct FTimerHandle;


UCLASS()
class FIXEDPOINT_API UBTTask_LarvaWallImpactStun : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

	AFixedPointLarvaCharacter* LarvaCharacter = nullptr;

	AFixedPointLarvaAIController* LarvaAIController = nullptr;

	UBlackboardComponent* BB = nullptr;

	FTimerHandle StunTimerHandle;

	UBTTask_LarvaWallImpactStun(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
