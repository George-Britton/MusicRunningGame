// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleSpawner.h"


// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the default objects and attaches to root
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->SetupAttachment(this->RootComponent);

}

// Called every SpawnFrequencyInSeconds seconds
void AObstacleSpawner::Spawn()
{
	// Chooses a random point within the spawn box and spawns an obstacle there
	const FVector SpawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(SpawnBox->GetComponentLocation(), SpawnBox->GetScaledBoxExtent());
	const FRotator SpawnRot(FQuat::Identity);
	FActorSpawnParameters SpawnParams;

	// Gets a reference to the new Obstacle and gives it the preset variables
	AObstacle* ObstacleRef = GetWorld()->SpawnActor<AObstacle>(ObstacleActor, SpawnLoc, SpawnRot, SpawnParams);
	ObstacleRef->ObstacleMesh = ObstacleMeshes[FMath::RandRange(0, ObstacleMeshes.Num() - 1)];
	ObstacleRef->Speed = Speed;
	ObstacleRef->ObstacleDirection = ObstacleDirection;

}
