// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Obstacle.generated.h"

UENUM()
enum class ObstacleDirectionEnum : uint8{
	LeftDirection UMETA(DisplayName = "Left"),
	RightDirection UMETA(DisplayName = "Right"),
	UpDirection UMETA(DisplayName = "Up"),
	DownDirection UMETA(DisplayName = "Down"),
	NoDirection UMETA(DisplayName = "None"),
};

UCLASS()
class MUSICRUNNINGGAME_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	// Static mesh that represents the obstacle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		UStaticMesh* ObstacleMesh;
	UPROPERTY()
		UStaticMeshComponent* ObstacleMeshComponent;
	UPROPERTY()
		bool MeshSet = false;

	// Enum dictating the direction the obstacle should move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		ObstacleDirectionEnum ObstacleDirection = ObstacleDirectionEnum::NoDirection;

	// Speed at which the obstacle moves
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		float Speed = 5;


	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
};
