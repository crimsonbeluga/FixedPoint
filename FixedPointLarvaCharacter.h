// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "../FixedPoint/AI/Characters/FixedPointAICharacter.h"
#include "FixedPointLarvaCharacter.generated.h"

/**
 * 
 */

class AFixedPointPatrolPoint;
UCLASS()
class FIXEDPOINT_API AFixedPointLarvaCharacter : public AFixedPointAICharacter
{
	GENERATED_BODY()
public:

    const TArray<TObjectPtr<AFixedPointPatrolPoint>>& GetPatrolPoints() const
    {
        return PatrolPoints;
    }

protected:

UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AI | Patrol")
TArray<TObjectPtr<AFixedPointPatrolPoint>> PatrolPoints;




private:


};
