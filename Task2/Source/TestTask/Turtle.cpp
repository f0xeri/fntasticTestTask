// Fill out your copyright notice in the Description page of Project Settings.


#include "Turtle.h"

// Sets default values
ATurtle::ATurtle()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible component"));
	DestructibleComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UDestructibleMesh> Sphere(TEXT("DestructibleMesh'/Game/Meshes/Sphere_DM.Sphere_DM'"));
	DestructibleComponent->SetDestructibleMesh(Sphere.Object);
	if (Sphere.Succeeded())
	{
		DestructibleComponent->SetDestructibleMesh(Sphere.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> SpawnSoundResource(TEXT("SoundCue'/Game/Sounds/SpawnSoundCue.SpawnSoundCue'"));
	if (SpawnSoundResource.Succeeded())
	{
		SpawnSoundCue = SpawnSoundResource.Object;
		SpawnAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SpawnAudioComponent"));
		SpawnAudioComponent->SetupAttachment(RootComponent);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> MovingSoundResource(TEXT("SoundCue'/Game/Sounds/MovingSoundCue.MovingSoundCue'"));
	if (MovingSoundResource.Succeeded())
	{
		MovingSoundCue = MovingSoundResource.Object;
		MainAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MovingAudioComponent"));
		MainAudioComponent->SetupAttachment(RootComponent);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> FinishSoundResource(TEXT("SoundCue'/Game/Sounds/FinishSoundCue.FinishSoundCue'"));
	if (FinishSoundResource.Succeeded())
	{
		FinishSoundCue = FinishSoundResource.Object;
		MainAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FinishAudioComponent"));
		MainAudioComponent->SetupAttachment(RootComponent);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> MovingParticleResource(TEXT("ParticleSystem'/Game/ParticleSystems/MovingParticleSystem.MovingParticleSystem'"));
	if (MovingParticleResource.Succeeded())
	{
		MovingParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovingParticleSystem"));
		MovingParticleSystem->bAutoActivate = true;
		MovingParticleSystem->SetTemplate(MovingParticleResource.Object);
		MovingParticleSystem->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void ATurtle::BeginPlay()
{
	Super::BeginPlay();

	SpawnAudioComponent->SetSound(SpawnSoundCue);
	SpawnAudioComponent->Play();

	MainAudioComponent->SetSound(MovingSoundCue);
	MainAudioComponent->Play();
	MovingParticleSystem->AttachTo(DestructibleComponent);
	ChangeSpeed();
}

// Called every frame
void ATurtle::Tick(float DeltaTime)
{
	CurrentLocation = this->GetActorLocation();
	if (CurrentLocation.X < 410)
	{
		CurrentLocation.X += CurrentSpeed * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
	else if (!finished)
	{
		finished = true;
		MainAudioComponent->SetSound(nullptr);
		UGameplayStatics::PlaySound2D(this, FinishSoundCue);
		DestructibleComponent->ApplyRadiusDamage(10, CurrentLocation, 30, 1, true);
		MovingParticleSystem->DeactivateSystem();
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATurtle::Finished, 5.0f, false);
	}
}

void ATurtle::ChangeSpeed()
{
	CurrentSpeed = CurrentDirection ? posSpeed : negSpeed;
	CurrentDirection = !CurrentDirection;
	if (CurrentDirection)
	{
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATurtle::ChangeSpeed, 0.5f, false);
	}
	else
	{
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATurtle::ChangeSpeed, 1.0f, false);
	}
}

void ATurtle::Finished()
{
	Destroy();
}
