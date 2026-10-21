// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointPatrolPoint.h"
#include "Components/ArrowComponent.h"


// Sets default values
AFixedPointPatrolPoint::AFixedPointPatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	SetRootComponent(StaticMesh);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction Arrow"));

	DirectionArrow->SetupAttachment(RootComponent);

	DirectionArrow->ArrowColor = FColor::Red;

	DirectionArrow->SetRelativeLocation(FVector(0, 0, 15));
}

// Called when the game starts or when spawned
void AFixedPointPatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFixedPointPatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

