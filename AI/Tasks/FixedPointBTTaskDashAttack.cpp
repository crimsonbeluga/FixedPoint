// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointBTTaskDashAttack.h"
#include "../Controllers/FixedPointLarvaAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Player/Characters/FixedPointCharacter.h"
#include "../Characters/FixedPointLarvaCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Engine/TimerHandle.h"






DEFINE_LOG_CATEGORY(LogFixedPointBTTaskDashAttack);


UFixedPointBTTaskDashAttack::UFixedPointBTTaskDashAttack(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	// sets  the node to tick every frame while active 
	bNotifyTick = true;

	// sets the node to create an instance of itself for each behavior tree that uses it
	bCreateNodeInstance = true;
}


EBTNodeResult::Type UFixedPointBTTaskDashAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;

	LarvaAIController = Cast<AFixedPointLarvaAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(LarvaAIController))
	{
		UE_LOG(LogFixedPointBTTaskDashAttack, Warning, TEXT("ExecuteTask() | LocalLarvaAIController is not valid "));

		return EBTNodeResult::Failed;
	}

	LarvaCharacter = Cast<AFixedPointLarvaCharacter>(LarvaAIController->GetPawn());

	if (!IsValid(LarvaCharacter))
	{
			UE_LOG(LogFixedPointBTTaskDashAttack, Warning, TEXT("ExecuteTask() | The LarvaCharacter is not valid "));

		return EBTNodeResult::Failed;
	}

	BB = OwnerComp.GetBlackboardComponent();

	if (!IsValid(BB))
	{
		UE_LOG(LogFixedPointBTTaskDashAttack, Warning, TEXT("ExecuteTask() | The Blackboard Component is not valid "));

		 return EBTNodeResult::Failed;
	}
	

	TargetActor = Cast<AFixedPointCharacter>(BB->GetValueAsObject(TEXT("Target Actor")));

	if (!IsValid(TargetActor))
	{
		UE_LOG(LogFixedPointBTTaskDashAttack, Warning, TEXT("ExecuteTask() | TargetActor is not valid "));

		return EBTNodeResult::Failed;

	}

	DashRotation = LarvaCharacter->GetActorRotation();

	LarvaCharacter->SetMovementState(EMovementState::Dash);

	GetWorld()->GetTimerManager().SetTimer(DashStunBufferTimer,)
	return EBTNodeResult::InProgress;







}

void UFixedPointBTTaskDashAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// get the Location of the target actor 
	if (!IsValid(TargetActor))
	{
		UE_LOG(LogFixedPointBTTaskDashAttack, Warning,
			TEXT("TickTask() | TargetActor is not valid"));

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (!IsValid(LarvaCharacter))
	{
		UE_LOG(LogFixedPointBTTaskDashAttack, Warning,
			TEXT("TickTask() | LarvaCharacter is not valid"));

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (!IsValid(LarvaAIController))
	{
		UE_LOG(LogFixedPointBTTaskDashAttack, Warning,
			TEXT("TickTask() | LarvaAIController is not valid"));

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if(HasDashStalled())
	{
		LarvaAIController->SetBlackBoardKeyIsStunned(true);
		return;
	}
		


	UpdateDashMovement(DeltaSeconds);
	



}


void UFixedPointBTTaskDashAttack::UpdateDashMovement(float DeltaSeconds)
{


	FVector LarvaLocation = LarvaCharacter->GetActorLocation();

	FVector TargetActorLocation = TargetActor->GetActorLocation();

	FRotator GoalRotation = UKismetMathLibrary::FindLookAtRotation(LarvaLocation, TargetActorLocation);

	FRotator GoalRotationYaw = FRotator(0.f, GoalRotation.Yaw, 0.f);



	DashRotation = FMath::RInterpConstantTo(DashRotation, GoalRotationYaw, DeltaSeconds, LarvaCharacter->GetDashTurnRate());

	FVector MovementDirection = UKismetMathLibrary::GetForwardVector(DashRotation);

	LarvaCharacter->AddMovementInput(MovementDirection, 1.0f);
}

bool UFixedPointBTTaskDashAttack::HasDashStalled()
{
	float LocalDashSpeed = LarvaCharacter->GetVelocity().Size2D();

	float LocalDashStopSpeedReductionThreshold = LarvaCharacter->GetDashStopSpeedReductionThreshold();

	// if are current speed is slower then the dash speed reduction  threshold
	if (LocalDashSpeed <= LocalDashSpeed * LocalDashStopSpeedReductionThreshold)
	{
		return true;
	}

	return false;
}

