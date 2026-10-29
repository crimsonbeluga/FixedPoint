// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "FixedPointAICharacter.h"
#include "FixedPointLarvaCharacter.generated.h"

/**
 * 
 */





UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Patrol UMETA(DisplayName = "Patrol"),
	Roar UMETA(DisplayName = "Roar"),
	Dash UMETA(DisplayName = "Dash"),
	Stun UMETA(DisplayName = "Stun")
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnMovementStateChanged,
	EMovementState,
	NewMovementState
);

class AFixedPointPatrolPoint;
UCLASS()
class FIXEDPOINT_API AFixedPointLarvaCharacter : public AFixedPointAICharacter
{
	GENERATED_BODY()
public:

    virtual void BeginPlay() override;

    AFixedPointLarvaCharacter();

    const TArray<TObjectPtr<AFixedPointPatrolPoint>>& GetPatrolPoints() const
    {
        return PatrolPoints;
    }

	float GetDashTurnRate() const
	{
		return DashTurnRate;
	}

	float GetDashSpeed() const
	{
		return DashSpeed;
	}

	float GetRoarSpeed() const
	{
		return RoarSpeed;
	}

	float GetStunSpeed() const
	{
		return StunSpeed;
	}

	float GetPatrolSpeed() const
	{
		return PatrolSpeed;
	}

	float GetDashStopSpeedReductionThreshold() const
	{
		return DashStopSpeedReductionThreshold;
	}						   

	float GetStunStateDuration() const
	{
		return StunStateDuration;
	}
	


	void SetMovementState(EMovementState NewState);

	EMovementState GetMovementState() const
	{
		return MovementState;
	}

protected:

UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AI | Patrol")
TArray<TObjectPtr<AFixedPointPatrolPoint>> PatrolPoints;

// how many degrees per second the larva can turn while dashing
UPROPERTY(EditDefaultsOnly, Category = "AI | Dash")
float DashTurnRate = 45.f;

UPROPERTY(EditDefaultsOnly, Category = "AI | Dash")
float PatrolSpeed = 150.f;

UPROPERTY(EditDefaultsOnly, Category = "AI | Dash")
float DashSpeed = 1200.f;

UPROPERTY(EditDefaultsOnly, Category = "AI | Dash")
float RoarSpeed = 0.f;

UPROPERTY(EditDefaultsOnly, Category = "AI | Dash")
float StunSpeed = 0.f;


UPROPERTY(EditDefaultsOnly, Category = "AI | Dash")
float DashStopSpeedReductionThreshold = 0.8f;

UPROPERTY(EditDefaultsOnly, Category = "AI | Dash")
float StunStateDuration = 3.f;

UFUNCTION()
void OnRep_MovementState();

virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


UPROPERTY(ReplicatedUsing = OnRep_MovementState,BlueprintReadOnly, Category = "AI | Movement")
EMovementState MovementState = EMovementState::Patrol;

UPROPERTY(BlueprintAssignable, Category = "AI | Movement")
FOnMovementStateChanged OnMovementStateChanged;

private:


};
