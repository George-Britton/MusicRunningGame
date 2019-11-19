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
	this->MusicPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("Music Player"));
	this->AttackRoster = CreateDefaultSubobject<UDataTable>(TEXT("Attack Roster"));
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

	// Check Roster is loaded in
	if (AttackRoster)
	{
		// Gets the row numbers of Roster
		TArray<TArray<FString>> AttackStringArray = AttackRoster->GetTableData();
		
		for (int32 RosterFiller = 1; RosterFiller < AttackStringArray.Num(); RosterFiller++)
		{
			if (AttackStringArray[RosterFiller][1] == FString("ProjectileAttackType")) AttackRosterArray.Add(EAttackType::ProjectileAttackType);
			else if (AttackStringArray[RosterFiller][1] == FString("BeamAttackType")) AttackRosterArray.Add(EAttackType::BeamAttackType);
			else if (AttackStringArray[RosterFiller][1] == FString("WaveAttackType")) AttackRosterArray.Add(EAttackType::WaveAttackType);
			else if (AttackStringArray[RosterFiller][1] == FString("ConeAttackType")) AttackRosterArray.Add(EAttackType::ConeAttackType);
			else if (AttackStringArray[RosterFiller][1] == FString("MeleeAttackType")) AttackRosterArray.Add(EAttackType::MeleeAttackType);
			else if (AttackStringArray[RosterFiller][1] == FString("SpecialAttackType")) AttackRosterArray.Add(EAttackType::SpecialAttackType);
		}
		AttackRosterArray.Add(EAttackType::NoneAttackType);

		// Finds first attack type to telegraph
		EAttackType FirstAttackType = AttackRosterArray[0];
		float FirstTelegraphTime = 0.f;
		switch (FirstAttackType)
		{
		case EAttackType::ProjectileAttackType: FirstTelegraphTime = ProjectileTelegraphTime; break;
		case EAttackType::BeamAttackType: FirstTelegraphTime = BeamTelegraphTime; break;
		case EAttackType::WaveAttackType: FirstTelegraphTime = WaveTelegraphTime; break;
		case EAttackType::ConeAttackType: FirstTelegraphTime = ConeTelegraphTime; break;
		case EAttackType::MeleeAttackType: FirstTelegraphTime = MeleeTelegraphTime; break;
		case EAttackType::SpecialAttackType: FirstTelegraphTime = SpecialTelegraphTime; break;
		default: break;
		}

		// Starts the attacks
		FTimerHandle StartAttackingTimer;
		FTimerDelegate StartAttackingDelegate;
		StartAttackingDelegate.BindUFunction(this, FName("PrepareForAttack"), FirstAttackType);
		GetWorld()->GetTimerManager().SetTimer(StartAttackingTimer, StartAttackingDelegate, FirstTelegraphTime, false);

		if(Song)
		{
			MusicPlayer->SetSound(Song);
			MusicPlayer->Play();
		}
	}
}

// Called when the boss needs to be told to attack
void AMusicManager::PrepareForAttack(EAttackType MMAttackType)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, "Prepare");
	FTimerHandle TelegraphHandle;
	FTimerDelegate TelegraphDelegate;
	FName FunctionCall;
	float Delay = 0;
	float TelegraphTime = 0;
	switch(MMAttackType)
	{
	case EAttackType::ProjectileAttackType: FunctionCall = "TelegraphProjectile"; Delay = OncomingBarSpawnFrequency - ProjectileTelegraphTime; TelegraphTime = ProjectileTelegraphTime; break;
	case EAttackType::BeamAttackType: FunctionCall = "TelegraphBeam"; Delay = OncomingBarSpawnFrequency - BeamTelegraphTime; TelegraphTime = BeamTelegraphTime; break;
	case EAttackType::WaveAttackType:  FunctionCall = "TelegraphWave"; Delay = OncomingBarSpawnFrequency - WaveTelegraphTime; TelegraphTime = WaveTelegraphTime; break;
	default: break;
	}

	TelegraphDelegate.BindUFunction(BossReference, FunctionCall, Delay);
	GetWorld()->GetTimerManager().SetTimer(TelegraphHandle, TelegraphDelegate, TelegraphTime, false);

	EntryToRead++;

	if(AttackRosterArray[EntryToRead] != EAttackType::NoneAttackType)
	{
		SetupNextAttack();
	}
}

// Called when the Music Manager needs to cue the next telegraph
void AMusicManager::SetupNextAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, "Setup");
	FTimerHandle SetupHandle;
	FTimerDelegate SetupDelegate;
	EAttackType NextAttack;
	float SetupTime = 0;
	switch(AttackRosterArray[EntryToRead])
	{
	case EAttackType::ProjectileAttackType: NextAttack = EAttackType::ProjectileAttackType; SetupTime = OncomingBarSpawnFrequency - ProjectileTelegraphTime; break;
	case EAttackType::BeamAttackType: NextAttack = EAttackType::BeamAttackType; SetupTime = OncomingBarSpawnFrequency - BeamTelegraphTime; break;
	case EAttackType::WaveAttackType: NextAttack = EAttackType::WaveAttackType; SetupTime = OncomingBarSpawnFrequency - WaveTelegraphTime; break;
	default: break;
	}	

	SetupDelegate.BindUFunction(this, FName("PrepareForAttack"), NextAttack);
	GetWorld()->GetTimerManager().SetTimer(SetupHandle, SetupDelegate, SetupTime, false);
}

// Called when an oncoming bar needs to be spawned
void AMusicManager::SpawnBar()
{
	OncomingBarSpawnerReference->Spawn();
}