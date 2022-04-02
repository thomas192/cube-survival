// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CubeIntelligence.generated.h"

/**
 * 
 */
UCLASS()
class PROJETMONDEVIRTUEL_API ACubeIntelligence : public AAIController
{
	GENERATED_BODY()

public:
	ACubeIntelligence();

	void OnPossess(APawn* pion) override;

	uint8 cleCube;
	
private:
	UPROPERTY(transient)
		class UBlackboardComponent* tableauNoir;

	UPROPERTY(transient)
		class UBehaviorTreeComponent* comportement;

};
