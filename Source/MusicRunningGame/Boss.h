// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "BossAttackData.h"
#include "Boss.generated.h"


UCLASS()
class MUSICRUNNINGGAME_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss();

	// The Static mesh that will temporarily act as the boss image
	UPROPERTY(EditAnywhere, Category = "Boss Appearance", BlueprintReadWrite)
		UStaticMesh * BossBallTemp;
	UPROPERTY()
		UStaticMeshComponent * BossBallTempComponent;

	// A reference to the player
	UPROPERTY(EditAnywhere, Category = "Player")
		AActor * PlayerReference;

	// A reference to the attack data file
	UPROPERTY()
		UBossAttackData* BossAttackComp;

	// Timer handle with details about the Attack event
	UPROPERTY()
		FTimerHandle AttackTimer;

	// Timing of attacks to the music (in seconds)
	UPROPERTY(EditAnywhere, Category = "Attack", BlueprintReadWrite)
		float AttackTimingInSeconds = 3;

	// Array of all of the boss' attacks
	UPROPERTY(EditAnywhere, Category = "Attack", BlueprintReadWrite)
		TArray<FAttackData> BossAttacks;

	// Upcoming attacks
	UPROPERTY()
		uint8 UpcomingAttack;
	UPROPERTY()
		uint8 QueuedAttack;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called every time a value is changed
	virtual void OnConstruction(const FTransform &trans) override;

	// Called on every bar of music for the attack
	UFUNCTION(Category = "Attack")
		void Attack();
	
};