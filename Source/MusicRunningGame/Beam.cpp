// Fill out your copyright notice in the Description page of Project Settings.

#include "Beam.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABeam::ABeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetupAttachment(this->RootComponent);

}

// Called every frame
void ABeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Started && Mesh && PlayerReference)
	{
		SetActorRotation(FRotator(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), PlayerReference->GetActorLocation())));
		Started = true;
	} else if(Started && !TimerSet)
	{
		MeshComponent->SetStaticMesh(Mesh);
		FTimerHandle DeletionTimer; GetWorld()->GetTimerManager().SetTimer(DeletionTimer, this, &ABeam::DestroySelf, Duration, false);
		TimerSet = true;
	}

	
}

// Called when the attack hits anything
void ABeam::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor == PlayerReference)
	{
		PlayerReference->HitByBeam(this, Damage);
	}	
}

// Called when the beam's time is up
void ABeam::DestroySelf()
{
	this->Destroy();
}
