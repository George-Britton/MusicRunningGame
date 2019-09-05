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

	// Sets collision of the bar ISMs
	PrimaryStaticMeshComponent->SetCollisionProfileName("OverlapAll");
	PrimaryStaticMeshComponent->bGenerateOverlapEvents = true;
	SecondaryStaticMeshComponent->SetCollisionProfileName("OverlapAll");
	SecondaryStaticMeshComponent->bGenerateOverlapEvents = true;
	TertiaryStaticMeshComponent->SetCollisionProfileName("OverlapAll");
	TertiaryStaticMeshComponent->bGenerateOverlapEvents = true;
}

// Called every time a value is changed
void AOncomingBarSpawner::OnConstruction(const FTransform &trans)
{
	if (SpawnPoint){ SpawnPointComponent->SetStaticMesh(SpawnPoint); }
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
			ActiveSpawners = BarDetails.Num();
			ArrayCleansed = true;
		}
	}

	// Sets the connection bar variables
	if (ConnectionBarRef)
	{
		ConnectionBarRef->OncomingBarSpawnerRef = this;

		switch (ActiveSpawners)
		{
		case 3: ConnectionBarRef->TertiaryKey = BarDetails[2].Key;
				TertiaryStaticMeshComponent->SetStaticMesh(BarDetails[2].BarMesh);
		case 2: ConnectionBarRef->SecondaryKey = BarDetails[1].Key;
				SecondaryStaticMeshComponent->SetStaticMesh(BarDetails[1].BarMesh);
		case 1: ConnectionBarRef->PrimaryKey = BarDetails[0].Key;
				PrimaryStaticMeshComponent->SetStaticMesh(BarDetails[0].BarMesh);
				MeshesSet = true;
				break;
		default: break;
		}
	}

	Super::BeginPlay();
}

// Called every frame
void AOncomingBarSpawner::Tick(float DeltaTime)
{
	FTransform PrimaryTransform;
	FTransform SecondaryTransform;
	FTransform TertiaryTransform;
	// Updates the location of the bar transforms, and marks the last of each as dirty to affect the changes
	switch (ActiveSpawners)
	{
	case 3:	for (int32 TertiaryCounter = 0; TertiaryCounter < TertiaryStaticMeshComponent->GetInstanceCount() - 1; TertiaryCounter++)
			{
				TertiaryStaticMeshComponent->GetInstanceTransform(TertiaryCounter, TertiaryTransform, true);
				TertiaryTransform.SetLocation(FVector((TertiaryTransform.GetLocation().X - Speed), (TertiaryTransform.GetLocation().Y), (TertiaryTransform.GetLocation().Z)));
				TertiaryStaticMeshComponent->UpdateInstanceTransform(TertiaryCounter, TertiaryTransform, true ,false, true);
			}
			TertiaryStaticMeshComponent->GetInstanceTransform(TertiaryStaticMeshComponent->GetInstanceCount() - 1, TertiaryTransform, true);
			TertiaryTransform.SetLocation(FVector((TertiaryTransform.GetLocation().X - Speed), (TertiaryTransform.GetLocation().Y), (TertiaryTransform.GetLocation().Z)));
			TertiaryStaticMeshComponent->UpdateInstanceTransform(TertiaryStaticMeshComponent->GetInstanceCount() - 1, TertiaryTransform, true ,true, true);
	case 2:	for (int32 SecondaryCounter = 0; SecondaryCounter < SecondaryStaticMeshComponent->GetInstanceCount() - 1; SecondaryCounter++)
			{
				SecondaryStaticMeshComponent->GetInstanceTransform(SecondaryCounter, SecondaryTransform, true);
				SecondaryTransform.SetLocation(FVector((SecondaryTransform.GetLocation().X - Speed), (SecondaryTransform.GetLocation().Y), (SecondaryTransform.GetLocation().Z)));
				SecondaryStaticMeshComponent->UpdateInstanceTransform(SecondaryCounter, SecondaryTransform, true ,false, true);
			}
			SecondaryStaticMeshComponent->GetInstanceTransform(SecondaryStaticMeshComponent->GetInstanceCount() - 1, SecondaryTransform, true);
			SecondaryTransform.SetLocation(FVector((SecondaryTransform.GetLocation().X - Speed), (SecondaryTransform.GetLocation().Y), (SecondaryTransform.GetLocation().Z)));
			SecondaryStaticMeshComponent->UpdateInstanceTransform(SecondaryStaticMeshComponent->GetInstanceCount() - 1, SecondaryTransform, true ,true, true);
	case 1:	for (int32 PrimaryCounter = 0; PrimaryCounter < PrimaryStaticMeshComponent->GetInstanceCount() - 1; PrimaryCounter++)
			{
				PrimaryStaticMeshComponent->GetInstanceTransform(PrimaryCounter, PrimaryTransform, true);
				PrimaryTransform.SetLocation(FVector((PrimaryTransform.GetLocation().X - Speed), (PrimaryTransform.GetLocation().Y), (PrimaryTransform.GetLocation().Z)));
				PrimaryStaticMeshComponent->UpdateInstanceTransform(PrimaryCounter, PrimaryTransform, true ,false, true);
			}
			PrimaryStaticMeshComponent->GetInstanceTransform(PrimaryStaticMeshComponent->GetInstanceCount() - 1, PrimaryTransform, true);
			PrimaryTransform.SetLocation(FVector((PrimaryTransform.GetLocation().X - Speed), (PrimaryTransform.GetLocation().Y), (PrimaryTransform.GetLocation().Z)));
			PrimaryStaticMeshComponent->UpdateInstanceTransform(PrimaryStaticMeshComponent->GetInstanceCount() - 1, PrimaryTransform, true ,true, true);
			break;
	default: break;
	}
	PrimaryStaticMeshComponent->GetIn
}

// Called every SpawnFrequencyInSeconds seconds
void AOncomingBarSpawner::Spawn()
{
	if (MeshesSet)
	{
		int32 BarChooser = FMath::RandRange(0, BarDetails.Num() - 1);
		switch (BarChooser)
		{
		case 0:	PrimarySpawn(); break;
		case 1:	SecondarySpawn(); break;
		case 2:	TertiarySpawn(); break;
		default: break;
		}
	}
}

// Called when the corresponding bar type is chosen to be spawned
void AOncomingBarSpawner::PrimarySpawn()
{
	FTransform SpawnParams;
	SpawnParams.SetLocation(SpawnPointComponent->GetComponentLocation());
	PrimaryStaticMeshComponent->AddInstanceWorldSpace(SpawnParams);
}

void AOncomingBarSpawner::SecondarySpawn()
{
	FTransform SpawnParams;
	SpawnParams.SetLocation(SpawnPointComponent->GetComponentLocation());
	SecondaryStaticMeshComponent->AddInstanceWorldSpace(SpawnParams);
}

void AOncomingBarSpawner::TertiarySpawn()
{
	FTransform SpawnParams;
	SpawnParams.SetLocation(SpawnPointComponent->GetComponentLocation());
	TertiaryStaticMeshComponent->AddInstanceWorldSpace(SpawnParams);
}