// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointBTTaskSelectPoint.h"
#include "../Characters/FixedPointLarvaCharacter.h"
#include "../Controllers/FixedPointLarvaAIController.h"
#include "../Navigation/FixedPointPatrolPoint.h"

DEFINE_LOG_CATEGORY(LogFixedPointBTTaskSelectPoint);

 // Starts this task, should return Succeeded, Failed or InProgress (use FinishLatentTask() when returning InProgress) 
 // this function should be considered as const (don't modify state of object) if node is not instanced!
EBTNodeResult::Type UFixedPointBTTaskSelectPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the AI owner through the owneing comnonent of this task (the black board) then get the AI owner of the black board and cast that
	// AI controller it returns as are type of AFixedPointLarvaAIController
	AFixedPointLarvaAIController* LocalLarvaAIController = Cast<AFixedPointLarvaAIController>(OwnerComp.GetAIOwner());
	
	// if the larva ai controller is not valid return out of the function here
	if (!IsValid(LocalLarvaAIController))
	{
		UE_LOG(LogFixedPointBTTaskSelectPoint, Warning, TEXT("ExecuteTask() | the AFixedPointLarvaAIController is not valid The node result is Failed"));
		return EBTNodeResult::Failed;
	}

	LarvaController = LocalLarvaAIController;

	// use the LarvaAIController get the character this AI controls and cast it to are character type AFixedPointLarvaCharacter
	AFixedPointLarvaCharacter* LocalControlledLarvaCharacter = Cast<AFixedPointLarvaCharacter>(LocalLarvaAIController->GetCharacter());

	// if the Controlled larva character is not valid return out of the function here
	if (!IsValid(LocalControlledLarvaCharacter))
	{
		UE_LOG(LogFixedPointBTTaskSelectPoint, Warning, TEXT("ExecuteTask() | the AFixedPointLarvaCharacter is not valid The node result is Failed"));

		return EBTNodeResult::Failed;
	}
	 
	LarvaCharacter = LocalControlledLarvaCharacter;

	

	AFixedPointPatrolPoint* ChosenPatrolPoint = SelectNextPatrolPoint(LarvaCharacter->GetPatrolPoints());

	if (!IsValid(ChosenPatrolPoint))
	{
		UE_LOG(LogFixedPointBTTaskSelectPoint, Warning, TEXT("ExecuteTask() | the chosen patrol point is not valid"));

		return EBTNodeResult::Failed;

		

	}

	LocalLarvaAIController->SetBlackBoardKeyPatrolLocation(ChosenPatrolPoint->GetActorLocation());

	UE_LOG(LogFixedPointBTTaskSelectPoint, Log, TEXT("ExecuteTask() | The node result is: Succeeded"));

	return EBTNodeResult::Succeeded;
	
	


	



	
}



AFixedPointPatrolPoint* UFixedPointBTTaskSelectPoint::SelectNextPatrolPoint(const TArray<TObjectPtr<AFixedPointPatrolPoint>>& PatrolPoints)
{
	if (PatrolPoints.IsEmpty())
	{
		UE_LOG(LogFixedPointBTTaskSelectPoint, Warning, TEXT("SelectNextPatrolPoint() | the PatrolPoints Array  is empty"));

		return nullptr;
	}

	if (!IsValid(LarvaController))
	{
		UE_LOG(LogFixedPointBTTaskSelectPoint, Warning, TEXT("SelectNextPatrolPoint() | the LarvaController is not valid"));

		return nullptr;
	}
	
	// the current index starting at zero we are in the array of patrol points
	int32 LocCurrentPatrolPointIndex = LarvaController->CurrentPatrolPointIndex;

	// the amount of stored patrol points EX: if theres 5 patrol points it returns 5
	int32 PatrolPointArrayLength = PatrolPoints.Num(); 

	// if we have no set patrol point meaning we are starting fresh do this
	if (LocCurrentPatrolPointIndex == INDEX_NONE )
	{
		LarvaController->CurrentPatrolPointIndex = 0;

		UE_LOG(LogFixedPointBTTaskSelectPoint, Log, TEXT("SelectNextPatrolPoint() | The Returned Integer patrol point is: 0"));

		return PatrolPoints[0].Get();


	}

		//3                                4
	if (LocCurrentPatrolPointIndex + 1 >= PatrolPointArrayLength)
	{
		LarvaController->CurrentPatrolPointIndex = 0;


		UE_LOG(LogFixedPointBTTaskSelectPoint, Log, TEXT("SelectNextPatrolPoint() | The Returned Integer patrol point is: 0"));

		return PatrolPoints[0].Get();

	} 
	else
	{
		LarvaController->CurrentPatrolPointIndex = LocCurrentPatrolPointIndex += 1;
		
		UE_LOG(LogFixedPointBTTaskSelectPoint, Log, TEXT("SelectNextPatrolPoint() | The Returned Integer patrol point is: %d"), LocCurrentPatrolPointIndex);

		return PatrolPoints[LocCurrentPatrolPointIndex].Get();
	}
		
	


}