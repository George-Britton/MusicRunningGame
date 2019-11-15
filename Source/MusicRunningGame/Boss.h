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

// Struct with the boss' attack details
USTRUCT(BlueprintType)
struct FAttackDetails
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintreadWrite)
		UClass* AttackActor;

		UPROPERTY(EditAnywhere, BlueprintreadWrite)
		UStaticMesh* AttackMesh;

		UPROPERTY(EditAnywhere, BlueprintreadWrite)
		float AttackDamage;

		UPROPERTY(EditAnywhere, BlueprintreadWrite)
		float AttackSpeed;

		UPROPERTY(EditAnywhere, BlueprintreadWrite)
		float AttackTelegraphTime;

		UPROPERTY(EditAnywhere, BlueprintreadWrite)
		float AttackDuration;

		FAttackDetails() {
			AttackActor = nullptr;
			AttackMesh = nullptr;
			AttackDamage = 2;
			AttackSpeed = 3;
			AttackTelegraphTime = 0.1;
			AttackDuration = 1;
		}
};

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

	// Static mesh for the target
	UPROPERTY(EditAnywhere, Category = "Attacks")
		UClass* TargetClass;
	UPROPERTY()
		AActor* TargetRef;

	// The boss' attack variables
	UPROPERTY(EditAnywhere, Category = "Attacks")
		FAttackDetails ProjectileAttack;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		FAttackDetails BeamAttack;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		FAttackDetails WaveAttack;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		FAttackDetails MeleeAttack;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		FAttackDetails ConeAttack;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		FAttackDetails SpecialAttack;

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
		void TelegraphProjectile(float WaitTime);
	UFUNCTION()
		void SpawnProjectile();
	UFUNCTION()
		void TelegraphBeam(float WaitTime);
	UFUNCTION()
		void SpawnBeam();
	UFUNCTION()
		void TelegraphWave(float WaitTime);
	UFUNCTION()
		void SpawnWave();
	
};