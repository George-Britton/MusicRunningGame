// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "OncomingBar.generated.h"

UCLASS()
class MUSICRUNNINGGAME_API AOncomingBar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOncomingBar();

	// The mesh the bar uses
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		UStaticMesh* BarMesh;
	UPROPERTY()
		UStaticMeshComponent* BarMeshComponent;
	UPROPERTY()
		bool MeshSet = false;

	// The key needed to avoid the bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	   FKey Key;

	// Speed the bar moves at
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Speed = 5;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called every time a value is changed
	virtual void OnConstruction(const FTransform &trans) override;

	// Called when the bar hits anything
	UFUNCTION()
		void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
