// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Boss.h"
#include "BossAttackData.h"
#include "OncomingBarSpawner.h"
#include "Engine.h"
#include "MusicManager.generated.h"

class ABoss;
class AOncomingBarSpawner;

// Struct that holds the upcoming attack information
USTRUCT(BlueprintType)
struct FAttackRosta
{
    GENERATED_USTRUCT_BODY()
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAttackType AttackType;

	FAttackRosta()
	{
		AttackType = EAttackType::NoneAttackType;
	}

};

UCLASS()
class MUSICRUNNINGGAME_API AMusicManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicManager();

	// BPM of the song
	UPROPERTY(EditAnywhere, Category = "Music")
		float BPM;
	UPROPERTY()
		float OncomingBarSpawnFrequency;

	// Song and CSV of attack types
	UPROPERTY()
		UAudioComponent* MusicPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
		USoundCue* Song;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		UDataTable* AttackRosta;
		TArray<FAttackRosta*> AttackRostaArray;

	// Timer for attacks
	UPROPERTY()
		FTimerHandle AttackTimer;
	UPROPERTY()
		int32 EntryToRead = 0;

	// Reference to the oncoming bar spawner
	UPROPERTY(EditAnywhere, Category = "Oncoming Bar Spawner")
		AOncomingBarSpawner* OncomingBarSpawnerReference;
	UPROPERTY()
		FTimerHandle OncomingBarTimer;

	// Reference to the boss
	UPROPERTY()
		ABoss* BossReference;

	// How long the boss needs to telegraph each attack type
	UPROPERTY()
		float ProjectileTelegraphTime = 0;
	UPROPERTY()
		float BeamTelegraphTime = 0;
	UPROPERTY()
		float WaveTelegraphTime = 0;
	UPROPERTY()
		float MeleeTelegraphTime = 0;
	UPROPERTY()
		float ConeTelegraphTime = 0;
	UPROPERTY()
		float SpecialTelegraphTime = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called when the boss needs to telegraph
	UFUNCTION()
		void PrepareForAttack(EAttackType MMAttackType, TArray<FAttackRosta> Rosta);

	// Called when the Music Manager needs to cue the next telegraph
	UFUNCTION()
		void SetupNextAttack(TArray<FAttackRosta> Rosta);

	// Called when an oncoming bar needs to be spawned
	UFUNCTION()
		void SpawnBar();
};