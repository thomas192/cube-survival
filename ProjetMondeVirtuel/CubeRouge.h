// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cube.h"
#include "CubeRouge.generated.h"

/**
 * 
 */
UCLASS()
class PROJETMONDEVIRTUEL_API ACubeRouge : public ACube
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACubeRouge();

	void attraper_Implementation() override;
};
