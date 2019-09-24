// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MusicManager.h"


// Sets default values
AMusicManager::AMusicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->MusicPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicPlayer"));
	MusicPlayer->SetupAttachment(this->RootComponent);

}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();

	// Sets a timer for the oncoming bars
	if (OncomingBarSpawnerReference && BPM)
	{
		OncomingBarSpawnFrequency = BPM / 60;
		GetWorld()->GetTimerManager().SetTimer(OncomingBarTimer, this, &AMusicManager::SpawnBar, OncomingBarSpawnFrequency, true, OncomingBarSpawnFrequency);
		OncomingBarSpawnerReference->SpawnFrequencyInSeconds = OncomingBarSpawnFrequency;
	}

	if (MusicClips.Num() > 0)
	{
		// Plays the first music clip
		ClipToPlay = FMath::RandRange(0, MusicClips.Num()-1);
		MusicPlayer->SetSound(MusicClips[ClipToPlay].MusicClip);
		MusicPlayer->Play();

		// Sets a timer for the next clip
		GetWorld()->GetTimerManager().SetTimer(MusicTimer, this, &AMusicManager::PlayNextClip, MusicClips[ClipToPlay].MusicClip->GetDuration(), false);

		// Sets a timer for the first attack
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AMusicManager::PrepareForAttack, MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead].TimeStampInSeconds, false);
	}
}

 // Called when the music clip cycles
void AMusicManager::PlayNextClip()
{
	// Plays the next clip and sets the attack counter to 0
	NextEntryToRead = 0;
	ClipToPlay = FMath::RandRange(0, MusicClips.Num()-1);
	MusicPlayer->SetSound(MusicClips[ClipToPlay].MusicClip);

	// Sets a timer for the next clip
	GetWorld()->GetTimerManager().SetTimer(MusicTimer, this, &AMusicManager::PlayNextClip, MusicClips[ClipToPlay].MusicClip->GetDuration(), false);

	// Sets a timer for the next attack
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AMusicManager::PrepareForAttack, MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead].TimeStampInSeconds, false);

}

// Called when the boss needs to be told to attack
void AMusicManager::PrepareForAttack()
{
	SendAttack(MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead].AttackType);

	// Sets a timer for the next attack
	float Delay;
	if (NextEntryToRead + 1 < MusicClips[ClipToPlay].TimeStampsOfAttacks.Num())
	{
		Delay = MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead + 1].TimeStampInSeconds - MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead].TimeStampInSeconds;
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AMusicManager::PrepareForAttack, Delay, false);
	}

	NextEntryToRead++;
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