// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->TargetMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	TargetMeshComponent->SetupAttachment(this->RootComponent);

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	if(TargetMesh)
	TargetMeshComponent->SetStaticMesh(TargetMesh);
}
