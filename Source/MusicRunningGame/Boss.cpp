// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Boss.h"


// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates default components and 
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->BossBallTempComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BossBallTemp"));
	BossBallTempComponent->SetupAttachment(this->RootComponent);

}

// Called every time a value is changed
void ABoss::OnConstruction(const FTransform &trans)
{
	if (BossBallTemp){BossBallTempComponent->SetStaticMesh(BossBallTemp);}
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

	if(MusicManagerReference)
	{
		MusicManagerReference->ProjectileTelegraphTime = ProjectileTelegraphTime;
		MusicManagerReference->BeamTelegraphTime = BeamTelegraphTime;
		MusicManagerReference->WaveTelegraphTime = WaveTelegraphTime;
		MusicManagerReference->MeleeTelegraphTime = MeleeTelegraphTime;
		MusicManagerReference->ConeTelegraphTime = ConeTelegraphTime;
		MusicManagerReference->BossReference = this;
	}

}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called on every bar of music for the attack
void ABoss::Attack(EAttackType BossAttackType)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("BossAttack"));
}