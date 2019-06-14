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

	if (MusicClips.Num() > 0)
	{
		ClipToPlay = FMath::RandRange(0, MusicClips.Num()-1);
		MusicPlayer->SetSound(MusicClips[ClipToPlay].MusicClip);
		MusicPlayer->Play();

		GetWorld()->GetTimerManager().SetTimer(MusicTimer, this, &AMusicManager::PlayNextClip, MusicClips[ClipToPlay].MusicClip->GetDuration(), false);

		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AMusicManager::PrepareForAttack, MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead].TimeStampInSeconds, false);
	}
}

 // Called when the music clip cycles
void AMusicManager::PlayNextClip()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("PlayNextClip"));

	NextEntryToRead = 0;
	ClipToPlay = FMath::RandRange(0, MusicClips.Num()-1);
	MusicPlayer->SetSound(MusicClips[ClipToPlay].MusicClip);

	GetWorld()->GetTimerManager().SetTimer(MusicTimer, this, &AMusicManager::PlayNextClip, MusicClips[ClipToPlay].MusicClip->GetDuration(), false);
}

// Called when the boss needs to be told to attack
void AMusicManager::PrepareForAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("PrepareForAttack"));


	SendAttack(MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead].AttackType);

	if(NextEntryToRead + 1 < MusicClips[ClipToPlay].TimeStampsOfAttacks.Num() && NextEntryToRead){
		float Delay = (MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead + 1].TimeStampInSeconds) - (MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead].TimeStampInSeconds);
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AMusicManager::PrepareForAttack, Delay, false);
		NextEntryToRead++;
	}else if(NextEntryToRead + 1 < MusicClips[ClipToPlay].TimeStampsOfAttacks.Num() && !NextEntryToRead)
	{
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AMusicManager::PrepareForAttack, MusicClips[ClipToPlay].TimeStampsOfAttacks[NextEntryToRead].TimeStampInSeconds, false);
		NextEntryToRead++;
	}
}
void AMusicManager::SendAttack(EAttackType MMAttackType)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("MusicManagerAttack"));

	BossReference->Attack(MMAttackType);
}