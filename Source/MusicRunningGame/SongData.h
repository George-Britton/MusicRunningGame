// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Engine.h"
#include "SongData.generated.h"


USTRUCT(BlueprintType)
struct FClipData
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ClipName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> TimeStampsOfAttacks;

	FClipData()
	{
		ClipName = FString("N/A");
		TimeStampsOfAttacks.Init(1, 1);
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUSICRUNNINGGAME_API USongData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USongData();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};