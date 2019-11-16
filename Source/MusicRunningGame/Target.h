// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Target.generated.h"

UCLASS()
class MUSICRUNNINGGAME_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	UPROPERTY()
		UStaticMesh* TargetMesh;
	UPROPERTY()
		UStaticMeshComponent* TargetMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
