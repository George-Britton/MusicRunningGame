// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Obstacle.h"
#include "Kismet/KismetMathLibrary.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class MUSICRUNNINGGAME_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

	// How frequently the obstacles are spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		float SpawnFrequencyInSeconds;
	UPROPERTY()
		FTimerHandle SpawningTimer;

	// References to the obstacles to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		UClass* ObstacleActor;

	// The spawning box for the obstacles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		UBoxComponent* SpawnBox;

	// Variables for the obstacles to have
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		TArray<UStaticMesh*> ObstacleMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Variables")
		ObstacleDirectionEnum ObstacleDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Variables")
		float Speed = 5;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every SpawnFrequencyInSeconds seconds
	UFUNCTION(Category = "Spawner")
		void Spawn();
	
};
