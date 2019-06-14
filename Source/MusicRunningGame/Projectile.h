// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "PlayerPawn.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class APlayerPawn;

UCLASS()
class MUSICRUNNINGGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Mesh of the attack
	UPROPERTY(EditAnywhere, Category = "Appearance")
		UStaticMesh* Mesh;
	UPROPERTY()
		UStaticMeshComponent* MeshComponent;

	// Speed of the projectile's movement
	UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 3;

	// Variables needed to target the player
	UPROPERTY(EditAnywhere, Category = "Player")
		APlayerPawn* PlayerReference;
	UPROPERTY()
		FVector Trajectory;

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
