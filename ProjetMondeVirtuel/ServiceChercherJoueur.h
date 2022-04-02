// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ServiceChercherJoueur.generated.h"

/**
 * 
 */
UCLASS()
class PROJETMONDEVIRTUEL_API UServiceChercherJoueur : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UServiceChercherJoueur();
};
