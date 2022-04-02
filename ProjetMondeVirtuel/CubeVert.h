// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cube.h"
#include "CubeVert.generated.h"

/**
 * 
 */
UCLASS()
class PROJETMONDEVIRTUEL_API ACubeVert : public ACube
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACubeVert();

	void attraper_Implementation() override;
};
