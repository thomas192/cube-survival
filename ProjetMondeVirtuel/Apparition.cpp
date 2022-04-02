// Fill out your copyright notice in the Description page of Project Settings.

#include "Apparition.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
AApparition::AApparition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Créer le Box Component pour représenter le volume d'apparition
	this->zone = CreateDefaultSubobject<UBoxComponent>(TEXT("Zone d'apparition"));
	this->RootComponent = zone;

	// Définir la plage du délai d'apparition
	this->delaiApparitionMinimum = 2.0f;
	this->delaiApparitionMaximum = 7.0f;
}

FVector AApparition::getPointsAuHasard()
{
	FVector origine = this->getZone()->Bounds.Origin;
	FVector etendue = this->getZone()->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(origine, etendue);
}

void AApparition::setApparitionActive(bool bDevraitApparaitre)
{
	if (bDevraitApparaitre)
	{
		// Définir le minuteur de l'apparition
		delaiApparition = FMath::FRandRange(delaiApparitionMinimum, delaiApparitionMaximum);
		GetWorldTimerManager().SetTimer(minuteur, this, &AApparition::apparaitre, delaiApparition, false);
	}
	else
	{
		// Retirer le minuteur
		GetWorldTimerManager().ClearTimer(minuteur);
	}
}

void AApparition::apparaitre()
{
	// Vérifier que le monde est valide
	UWorld* monde = GetWorld();
	if (monde != NULL)
	{
		// Apparition CubeBleu
		// Obtenir un point d'apparition
		FVector point = this->getPointsAuHasard();
		// Obtenir une rotation au hasard pour le cube
		FRotator rotation;
		rotation.Yaw = FMath::FRand() * 360.0f;
		rotation.Pitch = FMath::FRand() * 360.0f;
		rotation.Roll = FMath::FRand() * 360.0f;
		// Définir les paramètres d'apparition
		FActorSpawnParameters parametres;
		parametres.Owner = this;
		parametres.Instigator = GetInstigator();
		// Faire apparaitre le cube
		ACube* const cubeBleuApparu = monde->SpawnActor<ACube>(this->objetCubeBleu, point, rotation, parametres);

		// Apparition CubeRouge
		point = this->getPointsAuHasard();
		rotation.Yaw = FMath::FRand() * 360.0f;
		rotation.Pitch = FMath::FRand() * 360.0f;
		rotation.Roll = FMath::FRand() * 360.0f;
		parametres.Instigator = GetInstigator();
		ACube* const cubeRougeApparu = monde->SpawnActor<ACube>(this->objetCubeRouge, point, rotation, parametres);

		// Apparition CubeVert
		point = this->getPointsAuHasard();
		rotation.Yaw = FMath::FRand() * 360.0f;
		rotation.Pitch = FMath::FRand() * 360.0f;
		rotation.Roll = FMath::FRand() * 360.0f;
		parametres.Instigator = GetInstigator();
		ACube* const cubeVertApparu = monde->SpawnActor<ACube>(this->objetCubeVert, point, rotation, parametres);
		
		// On rappelle la fonction
		delaiApparition = FMath::FRandRange(delaiApparitionMinimum, delaiApparitionMaximum);
		GetWorldTimerManager().SetTimer(minuteur, this, &AApparition::apparaitre, delaiApparition, false);
	}
}

// Called when the game starts or when spawned
void AApparition::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AApparition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

