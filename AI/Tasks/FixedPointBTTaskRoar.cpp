// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointBTTaskRoar.h"
#include "../Characters/FixedPointLarvaCharacter.h"
#include "../Controllers/FixedPointLarvaAIController.h"

DEFINE_LOG_CATEGORY(LogFixedPointBTTaskRoar);

EBTNodeResult::Type UFixedPointBTTaskRoar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	LarvaAIController = Cast<AFixedPointLarvaAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(LarvaAIController))
	{
		UE_LOG(LogFixedPointBTTaskRoar, Warning, TEXT("ExecuteTask() | LocalLarvaAIController is not valid "));

		return EBTNodeResult::Failed;
	}

	LarvaCharacter = Cast<AFixedPointLarvaCharacter>(LarvaAIController->GetPawn());

	if (!IsValid(LarvaCharacter))
	{
		UE_LOG(LogFixedPointBTTaskRoar, Warning, TEXT("ExecuteTask() | The LarvaCharacter is not valid "));

		return EBTNodeResult::Failed;
	}						 

	LarvaCharacter->SetMovementState(EMovementState::Roar);


	return EBTNodeResult::Succeeded;
}
