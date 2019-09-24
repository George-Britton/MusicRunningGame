// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MusicManager.h"
#include "GameplayTagsManager.h"


// Sets default values
AMusicManager::AMusicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->MusicPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicPlayer"));
	this->AttackRosta = CreateDefaultSubobject<UDataTable>(TEXT("Attack Rosta"));
	MusicPlayer->SetupAttachment(this->RootComponent);

}

// Called every time a value is changed
void AMusicManager::OnConstruction(const FTransform &trans)
{
	/*
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT(""));

	FString RowHolder;
	AttackRosta->FindRow<FAttackRosta>(FName("1"), RowHolder, true);
	GLog->Log(RowHolder);
	*/
}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();

	// Sets a timer for the oncoming bars
	if (OncomingBarSpawnerReference && BPM)
	{
		OncomingBarSpawnFrequency = 60 / BPM;
		GetWorld()->GetTimerManager().SetTimer(OncomingBarTimer, this, &AMusicManager::SpawnBar, OncomingBarSpawnFrequency, true, OncomingBarSpawnFrequency);
		OncomingBarSpawnerReference->SpawnFrequencyInSeconds = OncomingBarSpawnFrequency;
	}

	
}

// Called when the boss needs to be told to attack
void AMusicManager::PrepareForAttack(EAttackType MMAttackType)
{
	EntryToRead++;
}
void AMusicManager::SendAttack(EAttackType MMAttackType)
{
	BossReference->Attack(MMAttackType);
}

// Called when an oncoming bar needs to be spawned
void AMusicManager::SpawnBar()
{
	OncomingBarSpawnerReference->Spawn();
}