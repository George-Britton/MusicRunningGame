// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "PlayerPawn.h"
#include "GameFramework/Actor.h"
#include "Beam.generated.h"

class APlayerPawn;

UCLASS()
class MUSICRUNNINGGAME_API ABeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeam();
	
	// Mesh of the attack
	UPROPERTY(EditAnywhere, Category = "Appearance")
		UStaticMesh* Mesh;
	UPROPERTY()
		UStaticMeshComponent* MeshComponent;

	// Duration of the beam
	UPROPERTY(EditAnywhere, Category = "Timing")
		float Duration = 0.3;

	// Variables needed to target the player
	UPROPERTY(EditAnywhere, Category = "Player")
		APlayerPawn* PlayerReference;
	UPROPERTY()
		FVector Trajectory;

	// Whether the attack has started
	UPROPERTY()
		bool Started = false;
	UPROPERTY()
		bool TimerSet = false;

	// Strength of the attack
	UPROPERTY(EditAnywhere, Category = "Damage")
		float Damage = 3;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the attack hits anything
	UFUNCTION()
		void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Called when the beam's time is up
	UFUNCTION()
		void DestroySelf();
};
