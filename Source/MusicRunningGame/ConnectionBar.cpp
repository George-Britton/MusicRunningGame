// Fill out your copyright notice in the Description page of Project Settings.

#include "ConnectionBar.h"


// Sets default values
AConnectionBar::AConnectionBar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the default objects and attaches to root
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->ConnectionBarMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Connection Bar Component"));
	ConnectionBarMeshComponent->SetupAttachment(this->RootComponent);

	ConnectionBarMeshComponent->SetCollisionProfileName("OverlapAll");
	ConnectionBarMeshComponent->bGenerateOverlapEvents = true;
	/*
	this->AutoReceiveInput = EAutoReceiveInput::Player0;
	this->InputComponent->bBlockInput = false;
	*/
}

// Called every time a value is changed
void AConnectionBar::OnConstruction(const FTransform& trans)
{
	if (ConnectionBarMesh){ ConnectionBarMeshComponent->SetStaticMesh(ConnectionBarMesh); }
}

// Called when the game starts or when spawned
void AConnectionBar::BeginPlay()
{
	Super::BeginPlay();
	/*
	// Binds key input to relevant functions
	InputComponent->BindKey(PrimaryKey, IE_Pressed,this, &AConnectionBar::PrimaryKeyPress);
	InputComponent->BindKey(SecondaryKey, IE_Pressed,this, &AConnectionBar::SecondaryKeyPress);
	InputComponent->BindKey(TertiaryKey, IE_Pressed,this, &AConnectionBar::TertiaryKeyPress);
	*/
}

// Called when the primary key is pressed
void AConnectionBar::PrimaryKeyPress()
{
	bool bPrimaryOverlapping = false;
	int32 OverlapIndex = 0;
	float ConnectionBarHeight = ConnectionBarMesh->GetBoundingBox().GetSize().X;
	float ConnectionBarLocation = ConnectionBarMeshComponent->GetComponentLocation().X;
	float PrimaryBarHeight = OncomingBarSpawnerRef->PrimaryStaticMeshComponent->GetStaticMesh()->GetBoundingBox().GetSize().X;
	float PrimaryBarLocation;
	FTransform CheckingTransform;

	// Loops through the primary bars to find which one, if any, is overlapping
	for (int32 InstanceFinder = 0; InstanceFinder < OncomingBarSpawnerRef->PrimaryStaticMeshComponent->GetInstanceCount(); InstanceFinder++)
	{
		OncomingBarSpawnerRef->PrimaryStaticMeshComponent->GetInstanceTransform(InstanceFinder, CheckingTransform, true);
		PrimaryBarLocation = CheckingTransform.GetLocation().X;
		
		if ((PrimaryBarLocation + (PrimaryBarHeight / 2) < (ConnectionBarLocation - (ConnectionBarHeight / 2)))){ continue; }
		if ((PrimaryBarLocation - (PrimaryBarHeight / 2) > (ConnectionBarLocation + (ConnectionBarHeight / 2)))){ continue; }

		bPrimaryOverlapping = true;
		OverlapIndex = InstanceFinder;
		break;
	}

	if (bPrimaryOverlapping)
	{
		OncomingBarSpawnerRef->PrimaryStaticMeshComponent->RemoveInstance(OverlapIndex);
	}
}

// Called when the secondary key is pressed
void AConnectionBar::SecondaryKeyPress()
{
	bool bSecondaryOverlapping = false;
	int32 OverlapIndex = 0;
	float ConnectionBarHeight = ConnectionBarMesh->GetBoundingBox().GetSize().X;
	float ConnectionBarLocation = ConnectionBarMeshComponent->GetComponentLocation().X;
	float SecondaryBarHeight = OncomingBarSpawnerRef->SecondaryStaticMeshComponent->GetStaticMesh()->GetBoundingBox().GetSize().X;
	float SecondaryBarLocation;
	FTransform CheckingTransform;

	// Loops through the primary bars to find which one, if any, is overlapping
	for (int32 InstanceFinder = 0; InstanceFinder < OncomingBarSpawnerRef->SecondaryStaticMeshComponent->GetInstanceCount(); InstanceFinder++)
	{
		OncomingBarSpawnerRef->SecondaryStaticMeshComponent->GetInstanceTransform(InstanceFinder, CheckingTransform, true);
		SecondaryBarLocation = CheckingTransform.GetLocation().X;
		
		if ((SecondaryBarLocation + (SecondaryBarHeight / 2) < (ConnectionBarLocation - (ConnectionBarHeight / 2)))){ continue; }
		if ((SecondaryBarLocation - (SecondaryBarHeight / 2) > (ConnectionBarLocation + (ConnectionBarHeight / 2)))){ continue; }

		bSecondaryOverlapping = true;
		OverlapIndex = InstanceFinder;
		break;
	}

	if (bSecondaryOverlapping)
	{
		OncomingBarSpawnerRef->SecondaryStaticMeshComponent->RemoveInstance(OverlapIndex);
	}
}

// Called when the tertiary key is pressed
void AConnectionBar::TertiaryKeyPress()
{
	bool bTertiaryOverlapping = false;
	int32 OverlapIndex = 0;
	float ConnectionBarHeight = ConnectionBarMesh->GetBoundingBox().GetSize().X;
	float ConnectionBarLocation = ConnectionBarMeshComponent->GetComponentLocation().X;
	float TertiaryBarHeight = OncomingBarSpawnerRef->TertiaryStaticMeshComponent->GetStaticMesh()->GetBoundingBox().GetSize().X;
	float TertiaryBarLocation;
	FTransform CheckingTransform;

	// Loops through the primary bars to find which one, if any, is overlapping
	for (int32 InstanceFinder = 0; InstanceFinder < OncomingBarSpawnerRef->TertiaryStaticMeshComponent->GetInstanceCount(); InstanceFinder++)
	{
		OncomingBarSpawnerRef->TertiaryStaticMeshComponent->GetInstanceTransform(InstanceFinder, CheckingTransform, true);
		TertiaryBarLocation = CheckingTransform.GetLocation().X;
		
		if ((TertiaryBarLocation + (TertiaryBarHeight / 2) < (ConnectionBarLocation - (ConnectionBarHeight / 2)))){ continue; }
		if ((TertiaryBarLocation - (TertiaryBarHeight / 2) > (ConnectionBarLocation + (ConnectionBarHeight / 2)))){ continue; }

		bTertiaryOverlapping = true;
		OverlapIndex = InstanceFinder;
		break;
	}

	if (bTertiaryOverlapping)
	{
		OncomingBarSpawnerRef->TertiaryStaticMeshComponent->RemoveInstance(OverlapIndex);
	}
}