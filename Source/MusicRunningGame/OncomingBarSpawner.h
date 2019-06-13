// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "OncomingBar.h"
#include "OncomingBarSpawner.generated.h"

USTRUCT(BlueprintType)
struct FBarData
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* BarMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FKey Key;

	FBarData()
	{
		BarMesh = nullptr;
		FKey Key;
	}

};


UCLASS()
class MUSICRUNNINGGAME_API AOncomingBarSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOncomingBarSpawner();

	// How frequently the bars are spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		float SpawnFrequencyInSeconds = 0.6122;
	UPROPERTY()
		FTimerHandle SpawningTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		UClass* BarActor;

	// Spawning point for the bars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		UStaticMesh* SpawnPoint;
	UPROPERTY()
		UStaticMeshComponent* SpawnPointComponent;

	// Variables to give to the oncoming bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bar Variables")
		float Speed = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bar Variables")
		TArray<FBarData> BarDetails;
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called every time a value is changed
	virtual void OnConstruction(const FTransform &trans) override;
	
	// Called every SpawnFrequencyInSeconds seconds
	UFUNCTION(Category = "Spawner")
		void Spawn();
};
