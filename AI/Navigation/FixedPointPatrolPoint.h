// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FixedPointPatrolPoint.generated.h"

UCLASS()
class FIXEDPOINT_API AFixedPointPatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFixedPointPatrolPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
