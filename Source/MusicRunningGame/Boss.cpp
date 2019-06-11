// Fill out your copyright notice in the Description page of Project Settings.

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

	if(!PlayerReference){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Please add a player reference"));}

	// Creates a timer delegate and uses it in a timed Attack event
		FTimerDelegate del;
		del.BindUObject(this, &ABoss::Attack);
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, del, AttackTimingInSeconds, true, 0);

}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Keeps the boss behind the player
	if(PlayerReference)
	{
		this->SetActorLocation(FVector(GetActorLocation().X, PlayerReference->GetActorLocation().Y, GetActorLocation().Z));
	}
}

// Called on every bar of music for the attack
void ABoss::Attack()
{
	
}