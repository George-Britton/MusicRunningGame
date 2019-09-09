// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "PlayerPawn.h"
#include "OncomingBarSpawner.h"
#include "Engine/InputKeyDelegateBinding.h"
#include "ConnectionBar.generated.h"

class AOncomingBarSpawner;
class APlayerPawn;

UCLASS()
class MUSICRUNNINGGAME_API AConnectionBar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConnectionBar();

	// Mesh of the connection bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* ConnectionBarMesh;
	UPROPERTY()
		UStaticMeshComponent* ConnectionBarMeshComponent;

	// Keys required to destroy overlapped bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keys")
		FKey PrimaryKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keys")
		FKey SecondaryKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keys")
		FKey TertiaryKey;

	// Reference to the player character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		APlayerPawn* PlayerRef;

	// Reference to the oncoming bar spawner
	UPROPERTY()
		AOncomingBarSpawner* OncomingBarSpawnerRef;
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every time a value is changed
	virtual void OnConstruction(const FTransform &trans) override;

	// Input actions
	UFUNCTION(BlueprintCallable, Category = "Input")
		void PrimaryKeyPress();
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SecondaryKeyPress();
	UFUNCTION(BlueprintCallable, Category = "Input")
		void TertiaryKeyPress();
};