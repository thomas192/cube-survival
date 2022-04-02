// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeVert.h"

// Sets default values for this actor's properties
ACubeVert::ACubeVert()
{
	this->getMailles()->SetSimulatePhysics(false);
	this->getMailles()->SetCastShadow(false);

	this->bonus = 30.0f;
}

void ACubeVert::attraper_Implementation()
{
	// Utiliser le comportement de base
	Super::attraper_Implementation();
	// Détruire le cube
	Destroy();
}
