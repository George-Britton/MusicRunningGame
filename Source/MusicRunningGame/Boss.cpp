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
		MusicManagerReference->ProjectileTelegraphTime = ProjectileAttack.AttackTelegraphTime;
		MusicManagerReference->BeamTelegraphTime = BeamAttack.AttackTelegraphTime;
		MusicManagerReference->WaveTelegraphTime = WaveAttack.AttackTelegraphTime;
		MusicManagerReference->MeleeTelegraphTime = MeleeAttack.AttackTelegraphTime;
		MusicManagerReference->ConeTelegraphTime = ConeAttack.AttackTelegraphTime;
		MusicManagerReference->SpecialTelegraphTime = SpecialAttack.AttackTelegraphTime;
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

	switch (BossAttackType)
	{
	case EAttackType::ProjectileAttackType : SpawnProjectile(); break;
	case EAttackType::BeamAttackType : SpawnBeam(); break;
	case EAttackType::WaveAttackType : SpawnWave(); break;
	}
}
void ABoss::TelegraphProjectile(float WaitTime)
{
	FTimerHandle ProjectileTimer;
	FTimerDelegate ProjectileDelegate;
	GetWorld()->GetTimerManager().SetTimer(ProjectileTimer, ProjectileDelegate, WaitTime ,false);
}
void ABoss::SpawnProjectile()
{
	const FVector SpawnLoc = GetActorLocation();
	const FRotator SpawnRot(FQuat::Identity);
	FActorSpawnParameters SpawnParams;

	// Gets a reference to the new projectile and gives it the preset variables
	AProjectile* ProjectileRef = GetWorld()->SpawnActor<AProjectile>(ProjectileAttack.AttackActor, SpawnLoc, SpawnRot, SpawnParams);
	ProjectileRef->Mesh = ProjectileAttack.AttackMesh;
	ProjectileRef->Damage = ProjectileAttack.AttackDamage;
	ProjectileRef->Speed = ProjectileAttack.AttackSpeed;
	ProjectileRef->PlayerReference = PlayerReference;
}
void ABoss::TelegraphBeam(float WaitTime)
{
	const FVector SpawnLoc = PlayerReference->GetActorLocation();
	const FRotator SpawnRot(FQuat::Identity);
	FActorSpawnParameters SpawnParams;

	TargetRef = GetWorld()->SpawnActor<AProjectile>(TargetClass, SpawnLoc, SpawnRot, SpawnParams);
	FTimerHandle BeamTimer;
	FTimerDelegate BeamDelegate;
	GetWorld()->GetTimerManager().SetTimer(BeamTimer, BeamDelegate, WaitTime ,false);
}
void ABoss::SpawnBeam()
{
	const FVector SpawnLoc = GetActorLocation();
	const FRotator SpawnRot(FQuat::Identity);
	FActorSpawnParameters SpawnParams;

	// Gets a reference to the new projectile and gives it the preset variables
	ABeam* BeamRef = GetWorld()->SpawnActor<ABeam>(BeamAttack.AttackActor, SpawnLoc, SpawnRot, SpawnParams);
	TargetRef->Destroy();
	BeamRef->Mesh = BeamAttack.AttackMesh;
	BeamRef->Damage = BeamAttack.AttackDamage;
	BeamRef->Duration = BeamAttack.AttackDuration;
	BeamRef->PlayerReference = PlayerReference;
}
void ABoss::TelegraphWave(float WaitTime)
{
	FTimerHandle WaveTimer;
	FTimerDelegate WaveDelegate;
	GetWorld()->GetTimerManager().SetTimer(WaveTimer, WaveDelegate, WaitTime ,false);
}
void ABoss::SpawnWave()
{
	const FVector SpawnLoc = GetActorLocation();
	const FRotator SpawnRot(FQuat::Identity);
	FActorSpawnParameters SpawnParams;

	// Gets a reference to the new projectile and gives it the preset variables
	AWave* WaveRef = GetWorld()->SpawnActor<AWave>(WaveAttack.AttackActor, SpawnLoc, SpawnRot, SpawnParams);
	WaveRef->Mesh = WaveAttack.AttackMesh;
	WaveRef->Damage = WaveAttack.AttackDamage;
	WaveRef->Speed = WaveAttack.AttackSpeed;
	WaveRef->PlayerReference = PlayerReference;
}
