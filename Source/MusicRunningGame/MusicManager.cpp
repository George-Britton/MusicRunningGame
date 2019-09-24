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

	TArray<FAttackRosta*> AttackRostaArray;
	//not null. we loaded something in. 
	if (this->AttackRosta) {

		TArray<FName> RowNumbers = AttackRosta->GetRowNames(); // row numbers
		FString ContextString;

		for (FName& Row : RowNumbers)
		{
			FAttackRosta* AttackType = AttackRosta->FindRow<FAttackRosta>(Row, ContextString);
			if(AttackType){ AttackRostaArray.Add(AttackType); }
		}
	}

	EAttackType FirstAttackType = AttackRostaArray[0].AttackType;
	float FirstTelegraphTime = 0.f;
	switch(AttackRostaArray[0].AttackType)
	{
	case EAttackType::ProjectileAttackType: FirstTelegraphTime = ProjectileTelegraphTime; break;
	case EAttackType::BeamAttackType: FirstTelegraphTime = BeamTelegraphTime; break;
	case EAttackType::WaveAttackType: FirstTelegraphTime = WaveTelegraphTime; break;
	case EAttackType::ConeAttackType: FirstTelegraphTime = ConeTelegraphTime; break;
	case EAttackType::MeleeAttackType: FirstTelegraphTime = MeleeTelegraphTime; break;
	case EAttackType::SpecialAttackType: FirstTelegraphTime = SpecialTelegraphTime; break;
	default: break;
	}

	FTimerHandle StartAttackingTimer;
	FTimerDelegate StartAttackingDelegate;
	StartAttackingDelegate.BindUFunction(this, FName("PrepareForAttack"), FirstAttackType, AttackRostaArray);
	GetWorld()->GetTimerManager().SetTimer(StartAttackingTimer, StartAttackingDelegate, FirstTelegraphTime, false);
	
}

// Called when the boss needs to be told to attack
void AMusicManager::PrepareForAttack(EAttackType MMAttackType, TArray<FAttackRosta> Rosta)
{
	FTimerHandle TelegraphHandle;
	FTimerDelegate TelegraphDelegate;
	float TelegraphTime = 0;
	switch(MMAttackType)
	{
	case EAttackType::ProjectileAttackType: TelegraphDelegate.BindUFunction(BossReference, FName("TelegraphProjectile"), (OncomingBarSpawnFrequency - ProjectileTelegraphTime)); TelegraphTime = ProjectileTelegraphTime; break;
	case EAttackType::BeamAttackType: TelegraphDelegate.BindUFunction(BossReference, FName("TelegraphBeam"), (OncomingBarSpawnFrequency - BeamTelegraphTime)); TelegraphTime = BeamTelegraphTime; break;
	case EAttackType::WaveAttackType: TelegraphDelegate.BindUFunction(BossReference, FName("TelegraphWave"), (OncomingBarSpawnFrequency - WaveTelegraphTime)); TelegraphTime = WaveTelegraphTime; break;
	default: break;
	}

	GetWorld()->GetTimerManager().SetTimer(TelegraphHandle, TelegraphDelegate, TelegraphTime, false);

	EntryToRead++;

	if(Rosta[EntryToRead].AttackType != EAttackType::NoneAttackType)
	{
		SetupNextAttack(Rosta);
	}
	
}

// Called when the Music Manager needs to cue the next telegraph
void AMusicManager::SetupNextAttack(TArray<FAttackRosta> Rosta)
{
	FTimerHandle SetupHandle;
	FTimerDelegate SetupDelegate;
	float SetupTime = 0;
	switch(Rosta[EntryToRead].AttackType)
	{
	case EAttackType::ProjectileAttackType: SetupDelegate.BindUFunction(this, FName("PrepareForAttack"), EAttackType::ProjectileAttackType, Rosta); SetupTime = OncomingBarSpawnFrequency - ProjectileTelegraphTime; break;
	case EAttackType::BeamAttackType: SetupDelegate.BindUFunction(this, FName("PrepareForAttack"), EAttackType::BeamAttackType, Rosta); SetupTime = OncomingBarSpawnFrequency - BeamTelegraphTime; break;
	case EAttackType::WaveAttackType: SetupDelegate.BindUFunction(this, FName("PrepareForAttack"), EAttackType::WaveAttackType, Rosta); SetupTime = OncomingBarSpawnFrequency - WaveTelegraphTime; break;
	default: break;
	}

	GetWorld()->GetTimerManager().SetTimer(SetupHandle, SetupDelegate, SetupTime, false);
}

// Called when an oncoming bar needs to be spawned
void AMusicManager::SpawnBar()
{
	OncomingBarSpawnerReference->Spawn();
}