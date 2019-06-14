// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "PlayerPawn.h"
#include "GameFramework/Actor.h"
#include "Wave.generated.h"

class APlayerPawn;

UCLASS()
class MUSICRUNNINGGAME_API AWave : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWave();
		// Mesh of the attack
	UPROPERTY(EditAnywhere, Category = "Appearance")
		UStaticMesh* Mesh;
	UPROPERTY()
		UStaticMeshComponent* MeshComponent;

	// Speed of the wave's movement
	UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 3;

	// Variables needed to target the player
	UPROPERTY(EditAnywhere, Category = "Player")
		APlayerPawn* PlayerReference;

	// Whether the attack has started
	UPROPERTY()
		bool Started = false;

	// Strength of the attack
	UPROPERTY(EditAnywhere, Category = "Damage")
		float Damage = 3;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the attack hits anything
	UFUNCTION()
		void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
