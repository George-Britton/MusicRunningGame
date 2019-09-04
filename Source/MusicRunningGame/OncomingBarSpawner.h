// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "ConnectionBar.h"
#include "OncomingBarSpawner.generated.h"

class AConnectionBar;

// Struct detailing the variables of the oncoming bars
USTRUCT(BlueprintType)
struct FBarData
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* BarMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	FBarData()
	{
		BarMesh = nullptr;
		FKey Key;
		Damage = 0;
	}

};

// Enum dictating the type of bar spawned
UENUM()
enum class EBarType : int8 {
	PrimaryBar UMETA(DisplayName = "Primary Bar"),
	SecondaryBar UMETA(DisplayName = "Secondary Bar"),
	TertiaryBar UMETA(DisplayName = "Tertiary Bar"),
	None UMETA(DisplayName = "None")
};

UCLASS()
class MUSICRUNNINGGAME_API AOncomingBarSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOncomingBarSpawner();

	// Reference to connection bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection Bar")
		AConnectionBar* ConnectionBarRef;

	// How frequently the bars are spawned
	UPROPERTY()
		float SpawnFrequencyInSeconds = 0.6122;
	UPROPERTY()
		FTimerHandle SpawningTimer;

	// Components that spawn the different bars
	UPROPERTY()
		UInstancedStaticMeshComponent* PrimaryStaticMeshComponent;
	UPROPERTY()
		UInstancedStaticMeshComponent* SecondaryStaticMeshComponent;
	UPROPERTY()
		UInstancedStaticMeshComponent* TertiaryStaticMeshComponent;

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

	// Array saying which order the bars were spawned in
	UPROPERTY()
		TArray<EBarType> BarTypeArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every time a value is changed
	virtual void OnConstruction(const FTransform &trans) override;
	
	// Called every SpawnFrequencyInSeconds seconds
	UFUNCTION(Category = "Spawner")
		void Spawn();

	// Called when the corresponding bar type is chosen to be spawned
	UFUNCTION(Category = "Spawner")
		void PrimarySpawn();
	UFUNCTION(Category = "Spawner")
		void SecondarySpawn();
	UFUNCTION(Category = "Spawner")
		void TertiarySpawn();
};
