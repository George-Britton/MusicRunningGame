// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "BossAttackData.h"
#include "MusicManager.h"
#include "Projectile.h"
#include "Beam.h"
#include "Wave.h"
#include "Boss.generated.h"

class AMusicManager;

UCLASS()
class MUSICRUNNINGGAME_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss();

	// The Static mesh that will temporarily act as the boss image
	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		UStaticMesh * BossBallTemp;
	UPROPERTY()
		UStaticMeshComponent * BossBallTempComponent;

	// Reference to the player
	UPROPERTY(EditAnywhere, Category = "Player")
		APlayerPawn* PlayerReference;

	// Reference to the music manager
	UPROPERTY(EditAnywhere, Category = "Player")
		AMusicManager* MusicManagerReference;

	// The boss' attack variables
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UClass* ProjectileActor;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UStaticMesh* ProjectileMesh;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float ProjectileDamage = 2;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float ProjectileSpeed = 3;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float ProjectileTelegraphTime = 0;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UClass* BeamActor;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UStaticMesh* BeamMesh;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float BeamDamage = 4;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float BeamDuration = 3;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float BeamTelegraphTime = 0;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UClass* WaveActor;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UStaticMesh* WaveMesh;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float WaveDamage = 5;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float WaveSpeed = 3;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float WaveTelegraphTime = 0;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UClass* MeleeActor;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UStaticMesh* MeleeMesh;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float MeleeDamage = 5;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float MeleeTelegraphTime = 0;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UClass* ConeActor;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UStaticMesh* ConeMesh;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float ConeDamage = 5;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float ConeTelegraphTime = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called every time a value is changed
	virtual void OnConstruction(const FTransform &trans) override;

	// Called on every bar of music for the attack
	UFUNCTION()
		void Attack(EAttackType AttackType);
	UFUNCTION()
		void SpawnProjectile();
	UFUNCTION()
		void SpawnBeam();
	UFUNCTION()
		void SpawnWave();
	
};