// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Turtle.h"
#include "BaseNest.generated.h"

UCLASS()
class TESTTASK_API ABaseNest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseNest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) 
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATurtle> ActorToSpawn;

	// For a function that does manipulate the object in some way.
    UFUNCTION(BlueprintCallable)
    void SpawnNewTurtle(FString objName);
};
