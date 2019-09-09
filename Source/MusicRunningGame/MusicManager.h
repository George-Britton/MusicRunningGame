// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boss.h"
#include "BossAttackData.h"
#include "OncomingBarSpawner.h"
#include "Engine.h"
#include "MusicManager.generated.h"

class ABoss;
class AOncomingBarSpawner;

USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* MusicClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAttackTime> TimeStampsOfAttacks;

	FAttackData()
	{
		MusicClip = nullptr;
		TimeStampsOfAttacks.Empty();
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

	// Array of music clips and attack types
	UPROPERTY(EditAnywhere, Category = "Music")
		TArray<FAttackData> MusicClips;
	UPROPERTY()
		UAudioComponent* MusicPlayer;
	UPROPERTY()
		int32 ClipToPlay;
	UPROPERTY()
		FTimerHandle MusicTimer;
	UPROPERTY()
		FTimerHandle AttackTimer;
	UPROPERTY()
		int32 NextEntryToRead = 0;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called when the music clip cycles
	UFUNCTION()
		void PlayNextClip();

	// Called when the boss needs to attack
	UFUNCTION()
		void PrepareForAttack();
	UFUNCTION()
		void SendAttack(EAttackType MMAttackType);

	// Called when an oncoming bar needs to be spawned
	UFUNCTION()
		void SpawnBar();
};