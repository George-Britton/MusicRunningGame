// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OncomingBar.h"
#include "Projectile.h"
#include "Beam.h"
#include "Wave.h"
#include "PlayerPawn.generated.h"

class AOncomingBar;
class AProjectile;
class ABeam;
class AWave;

UCLASS()
class MUSICRUNNINGGAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the oncoming bars hit the player
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void HitByOncomingBar(AOncomingBar* OncomingBar, FKey Key, float Damage);
		void HitByOncomingBar_Implementation(AOncomingBar* OncomingBar, FKey Key, float Damage){}

	// Called when the projectiles hit the player
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void HitByProjectile(AProjectile* Projectile, float Damage);
		void HitByProjectile_Implementation(AProjectile* Projectile, float Damage){}

	// Called when the beams hit the player
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void HitByBeam(ABeam* Beam, float Damage);
		void HitByBeam_Implementation(ABeam* Beam, float Damage){}

	// Called when the waves hit the player
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void HitByWave(AWave* Wave, float Damage);
		void HitByWave_Implementation(AWave* Wave, float Damage){}
	
};
