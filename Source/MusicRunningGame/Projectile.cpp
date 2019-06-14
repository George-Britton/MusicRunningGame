// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetupAttachment(this->RootComponent);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!Started && Mesh && PlayerReference)
	{
		MeshComponent->SetStaticMesh(Mesh);
		Trajectory = PlayerReference->GetActorLocation() - GetActorLocation();
		Trajectory.Normalize();
		Started = true;
	}else if(Started)
	{
		this->AddActorWorldOffset(Trajectory * Speed, true, nullptr, ETeleportType::None);
	}
}

// Called when the attack hits anything
void AProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor == PlayerReference)
	{
		PlayerReference->HitByProjectile(this, Damage);
		this->Destroy();
	}
}