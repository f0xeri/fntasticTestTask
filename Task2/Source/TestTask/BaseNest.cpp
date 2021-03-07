// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNest.h"

// Sets default values
ABaseNest::ABaseNest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ABaseNest::BeginPlay()	
{
	Super::BeginPlay();	
}

// Called every frame
void ABaseNest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseNest::SpawnNewTurtle(FString objName)
{
	FActorSpawnParameters SpawnParams;
	FTransform transform;
	float posSpeed = 50.0, negSpeed;
	if (objName == "Nest1") {
		transform.SetLocation({-410.0, -330.0, 64.0});
		negSpeed = 50.0;
	}
	else if (objName == "Nest2") {
		transform.SetLocation({ -410.0, 0.0, 64.0 });
		negSpeed = 0.0;
	}
	else if (objName == "Nest3") {
		transform.SetLocation({ -410.0, 330.0, 64.0 });
		negSpeed = -50.0;
	}
	ATurtle* spawnedTurtle = GetWorld()->SpawnActorDeferred<ATurtle>(ActorToSpawn, transform);
	spawnedTurtle->posSpeed = posSpeed;
	spawnedTurtle->negSpeed = negSpeed;
	UGameplayStatics::FinishSpawningActor(spawnedTurtle, transform);
}
