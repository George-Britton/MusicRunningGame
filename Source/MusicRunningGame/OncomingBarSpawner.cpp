// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingBarSpawner.h"
#include "Engine/InputAxisKeyDelegateBinding.h"


// Sets default values
AOncomingBarSpawner::AOncomingBarSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the default objects and attaches to root
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->SpawnPointComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint"));
	this->PrimaryStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Primary Static Mesh Spawner"));
	this->SecondaryStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Secondary Static Mesh Spawner"));
	this->TertiaryStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Tertiary Static Mesh Spawner"));
	SpawnPointComponent->SetupAttachment(this->RootComponent);
	PrimaryStaticMeshComponent->SetupAttachment(this->RootComponent);
	SecondaryStaticMeshComponent->SetupAttachment(this->RootComponent);
	TertiaryStaticMeshComponent->SetupAttachment(this->RootComponent);
	SpawnPointComponent->bHiddenInGame = true;
	SpawnPointComponent->SetWorldScale3D(FVector(0.2,0.2,0.2));

	// Initiates the array of spawned bars with a None index
	BarTypeArray.Init(EBarType::None, 1);

}

// Called every time a value is changed
void AOncomingBarSpawner::OnConstruction(const FTransform &trans)
{
	if (SpawnPoint){SpawnPointComponent->SetStaticMesh(SpawnPoint);}
	
}

// Called when the game starts or when spawned
void AOncomingBarSpawner::BeginPlay()
{
	// Makes sure the Bar array is full
	bool ArrayCleansed = false;
	while(!ArrayCleansed)
	{
		if (!BarDetails[BarDetails.Num() - 1].BarMesh || BarDetails[BarDetails.Num() - 1].Key.GetFName() == "None" || !BarDetails[BarDetails.Num() - 1].Damage)
		{
			BarDetails.Pop();
		}else
		{
			ArrayCleansed = true;
		}
	}

	// Sets the connection bar variables
	if (ConnectionBarRef)
	{
		ConnectionBarRef->OncomingBarSpawnerRef = this;

		switch (BarDetails.Num())
		{
		case 3: ConnectionBarRef->TertiaryKey = BarDetails[2].Key;
				TertiaryStaticMeshComponent->SetStaticMesh(BarDetails[2].BarMesh);
		case 2: ConnectionBarRef->SecondaryKey = BarDetails[1].Key;
				SecondaryStaticMeshComponent->SetStaticMesh(BarDetails[1].BarMesh);
		case 1: ConnectionBarRef->PrimaryKey = BarDetails[0].Key;
				PrimaryStaticMeshComponent->SetStaticMesh(BarDetails[0].BarMesh);
				break;
		default: break;
		}
	}

	// Creates a timer delegate and uses it in a timed spawn event
	FTimerDelegate SpawnDelegate;
	SpawnDelegate.BindUObject(this, &AOncomingBarSpawner::Spawn);
	GetWorld()->GetTimerManager().SetTimer(SpawningTimer, SpawnDelegate, SpawnFrequencyInSeconds, true, 0);
}

// Called every SpawnFrequencyInSeconds seconds
void AOncomingBarSpawner::Spawn()
{
	int8 BarChooser = FMath::RandRange(0, 2);
	switch (BarChooser)
	{
	case 0:	PrimarySpawn(); break;
	case 1:	SecondarySpawn(); break;
	case 2:	TertiarySpawn(); break;
	default: break;
	}

}

// Called when the corresponding bar type is chosen to be spawned
void AOncomingBarSpawner::PrimarySpawn()
{
	FTransform SpawnParams;
	SpawnParams.SetLocation(SpawnPointComponent->GetComponentLocation());
	PrimaryStaticMeshComponent->AddInstanceWorldSpace(SpawnParams);
	BarTypeArray[BarTypeArray.Num() - 1] = EBarType::PrimaryBar;
}
void AOncomingBarSpawner::SecondarySpawn()
{
	FTransform SpawnParams;
	SpawnParams.SetLocation(SpawnPointComponent->GetComponentLocation());
	SecondaryStaticMeshComponent->AddInstanceWorldSpace(SpawnParams);
	BarTypeArray[BarTypeArray.Num() - 1] = EBarType::SecondaryBar;
}
void AOncomingBarSpawner::TertiarySpawn()
{
	FTransform SpawnParams;
	SpawnParams.SetLocation(SpawnPointComponent->GetComponentLocation());
	TertiaryStaticMeshComponent->AddInstanceWorldSpace(SpawnParams);
	BarTypeArray[BarTypeArray.Num() - 1] = EBarType::TertiaryBar;
}