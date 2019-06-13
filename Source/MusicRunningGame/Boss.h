// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "BossAttackData.h"
#include "MusicManager.h"
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
	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		UStaticMeshComponent * BossBallTempComponent;

	// Reference to the player
	UPROPERTY(EditAnywhere, Category = "Player")
		AActor * PlayerReference;

	// Reference to the music manager
	UPROPERTY(EditAnywhere, Category = "Player")
		AMusicManager* MusicManagerReference;

	// How long the boss needs to telegraph each attack type
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float ProjectileTelegraphTime = 0;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float BeamTelegraphTime = 0;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float WaveTelegraphTime = 0;
	UPROPERTY(EditAnywhere, Category = "Attacks")
		float MeleeTelegraphTime = 0;
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
	
};