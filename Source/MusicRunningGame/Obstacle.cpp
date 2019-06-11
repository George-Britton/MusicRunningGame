// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"


// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create default objects and attach root
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->ObstacleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMeshComponent"));
	ObstacleMeshComponent->SetupAttachment(this->RootComponent);

}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ObstacleMesh && !MeshSet)
	{
		ObstacleMeshComponent->SetStaticMesh(ObstacleMesh);
		MeshSet = true;
	}

	switch(ObstacleDirection)
	{
	case ObstacleDirectionEnum::UpDirection:
		this->AddActorWorldOffset(FVector(Speed, 0, 0), true, nullptr, ETeleportType::None);
		break;
	case ObstacleDirectionEnum::DownDirection:
		this->AddActorWorldOffset(FVector(-Speed, 0, 0), true, nullptr, ETeleportType::None);
		break;
	case ObstacleDirectionEnum::LeftDirection:
		this->AddActorWorldOffset(FVector(0, -Speed, 0), true, nullptr, ETeleportType::None);
		break;
	case ObstacleDirectionEnum::RightDirection:
		this->AddActorWorldOffset(FVector(0, Speed, 0), true, nullptr, ETeleportType::None);
		break;
	default: break;
	}

}