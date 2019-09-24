// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Engine.h"
#include "BossAttackData.generated.h"

UENUM()
enum class EAttackType : uint8 {
	ProjectileAttackType UMETA(DisplayName = "Projectile"),
	BeamAttackType UMETA(DisplayName = "Beam"),
	WaveAttackType UMETA(DisplayName = "Wave"),
	MeleeAttackType UMETA(DisplayName = "Melee"),
	ConeAttackType UMETA(DisplayName = "Cone"),
	SpecialAttackType UMETA(DisplayName = "Special"),
	NoneAttackType UMETA(DisplayName = "None")
};

USTRUCT(BlueprintType)
struct FAttackTime
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAttackType AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeStampInSeconds;

	FAttackTime()
	{
		AttackType = EAttackType::NoneAttackType;
		TimeStampInSeconds = 0;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUSICRUNNINGGAME_API UBossAttackData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossAttackData();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};