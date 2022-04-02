// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeBleu.h"

// Sets default values for this actor's properties
ACubeBleu::ACubeBleu()
{
	this->getMailles()->SetSimulatePhysics(false);
	this->getMailles()->SetCastShadow(false);

	this->bonus = 2.5f;
}

void ACubeBleu::attraper_Implementation()
{
	// Utiliser le comportement de base
	Super::attraper_Implementation();
	// Détruire le cube
	Destroy();
}
