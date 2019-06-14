// Fill out your copyright notice in the Description page of Project Settings.

#include "Wave.h"


// Sets default values
AWave::AWave()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetupAttachment(this->RootComponent);

}

// Called every frame
void AWave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!Started && Mesh && PlayerReference)
	{
		MeshComponent->SetStaticMesh(Mesh);
		Started = true;
	}else if(Started)
	{
		MeshComponent->SetWorldScale3D(FVector((MeshComponent->GetComponentScale().X), (MeshComponent->GetComponentScale().Y + 0.1), (MeshComponent->GetComponentScale().Z)));
		AddActorWorldOffset(FVector(-Speed, 0, 0), true, nullptr, ETeleportType::None);
	}

}

// Called when the attack hits anything
void AWave::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor == PlayerReference)
	{
		PlayerReference->HitByWave(this, Damage);
	}
}