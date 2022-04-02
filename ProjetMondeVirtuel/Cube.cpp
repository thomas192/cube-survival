// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Tous les cubes commencent actifs */
	bEstActif = true;

	/* Créer le composant static mesh */
	this->mailles = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Maille cube"));
	this->RootComponent = this->mailles;
}

void ACube::attraper_Implementation()
{
	UE_LOG(LogClass, Log, TEXT("ACube::attraper_Implementation()"));
}

// Retourne l'état d'activité
bool ACube::estActif()
{
	return bEstActif;
}

// Change l'état d'activité
void ACube::setActif(bool nouvelEtat)
{
	bEstActif = nouvelEtat;
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Retourne le bonus du cube
float ACube::getBonus()
{
	return this->bonus;
}

// Multiplie le bonus du cube
void ACube::multiplierBonus(int multiplier)
{
	this->bonus = multiplier * this->bonus;
}
