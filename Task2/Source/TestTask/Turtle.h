// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Engine/Classes/Sound/SoundCue.h>
#include <Components/AudioComponent.h>
#include <DestructibleComponent.h>
#include "ParticleDefinitions.h"
#include "TimerManager.h"
#include "DestructibleMesh.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Turtle.generated.h"


UCLASS()
class TESTTASK_API ATurtle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurtle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UDestructibleComponent* DestructibleComponent;

	UPROPERTY(EditAnywhere)
		USoundCue* SpawnSoundCue;

	UPROPERTY(EditAnywhere)
		USoundCue* MovingSoundCue;

	UPROPERTY(EditAnywhere)
		USoundCue* FinishSoundCue;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* MovingParticleSystem;

	FVector CurrentLocation;
	int CurrentSpeed = 50;
	bool CurrentDirection = true;
	float posSpeed, negSpeed;

	FTimerHandle MemberTimerHandle;

private:
	UAudioComponent* SpawnAudioComponent;
	UAudioComponent* MainAudioComponent;
	bool finished = false;

	void ChangeSpeed();
	void Finished();
};
