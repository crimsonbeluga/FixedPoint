// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FixedPointAIController.generated.h"

UCLASS()
class FIXEDPOINT_API AFixedPointAIController : public AAIController
{
	GENERATED_BODY()

public:

	// LIFECYCLE

	AFixedPointAIController(const FObjectInitializer& ObjectInitializer);
};