// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LarvaWallImpactStun.h"
#include "../Controllers/FixedPointLarvaAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Characters/FixedPointLarvaCharacter.h"
#include "../../Player/Characters/FixedPointCharacter.h"
#include "TimerManager.h"
#include "Engine/TimerHandle.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY(LogBTTaskLarvaWallImpactStun);

UBTTask_LarvaWallImpactStun::UBTTask_LarvaWallImpactStun(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNodeInstance = true;
}



EBTNodeResult::Type UBTTask_LarvaWallImpactStun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogBTTaskLarvaWallImpactStun, Warning,
		TEXT("STUN TASK STARTED"));

	LarvaAIController = Cast<AFixedPointLarvaAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(LarvaAIController))
	{
		UE_LOG(LogBTTaskLarvaWallImpactStun, Warning, TEXT("ExecuteTask() | LocalLarvaAIController is not valid "));

		return EBTNodeResult::Failed;
	}

	LarvaCharacter = Cast<AFixedPointLarvaCharacter>(LarvaAIController->GetPawn());

	if (!IsValid(LarvaCharacter))
	{
		UE_LOG(LogBTTaskLarvaWallImpactStun, Warning, TEXT("ExecuteTask() | The LarvaCharacter is not valid "));

		return EBTNodeResult::Failed;
	}

	BB = OwnerComp.GetBlackboardComponent();

	if (!IsValid(BB))
	{
		UE_LOG(LogBTTaskLarvaWallImpactStun, Warning, TEXT("ExecuteTask() | The Blackboard Component is not valid "));

		return EBTNodeResult::Failed;
	}

	AFixedPointCharacter* ForgottenPlayer =
		Cast<AFixedPointCharacter>(
			BB->GetValueAsObject(TEXT("Target Actor"))
		);

	UAIPerceptionComponent* Perception =
		LarvaAIController->GetAIPerceptionComponent();

	if (IsValid(Perception))
	{
		Perception->SetSenseEnabled(
			UAISense_Sight::StaticClass(),
			false
		);

		if (IsValid(ForgottenPlayer))
		{
			Perception->ForgetActor(ForgottenPlayer);
		}
	}

	if (IsValid(ForgottenPlayer))
	{
		LarvaAIController->OnTargetSightLost(ForgottenPlayer);
	}
	else
	{
		LarvaAIController->ClearBlackBoardKeyTargetActor();
	}

	// The stun must happen even if the player is no longer visible.
	LarvaCharacter->SetMovementState(EMovementState::Stun);

	TWeakObjectPtr<AFixedPointLarvaAIController> WeakController = LarvaAIController;

	GetWorld()->GetTimerManager().SetTimer(
		StunTimerHandle,
		[WeakController]()
		{
			UE_LOG(LogBTTaskLarvaWallImpactStun, Warning,
				TEXT("STUN TIMER FIRED"));

			if (AFixedPointLarvaAIController* Controller = WeakController.Get())
			{
				Controller->SetBlackBoardKeyIsStunned(false);

				if (UAIPerceptionComponent* Perception = Controller->GetAIPerceptionComponent())
				{
					Perception->SetSenseEnabled(
						UAISense_Sight::StaticClass(),
						true
					);
				}

				UE_LOG(LogBTTaskLarvaWallImpactStun, Warning,
					TEXT("STUN RECOVERY COMPLETED"));
			}
			else
			{
				UE_LOG(LogBTTaskLarvaWallImpactStun, Error,
					TEXT("STUN TIMER | Controller is no longer valid"));
			}
		},
		LarvaCharacter->GetStunStateDuration(),
		false
	);

	return EBTNodeResult::InProgress;
}
