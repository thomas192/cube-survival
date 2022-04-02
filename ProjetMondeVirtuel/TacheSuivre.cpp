// Fill out your copyright notice in the Description page of Project Settings.


#include "TacheSuivre.h"
#include "Engine/Engine.h"
#include "CubeIntelligence.h"
#include "ProjetMondeVirtuelCharacter.h"
#include "CubeCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UTacheSuivre::ExecuteTask(UBehaviorTreeComponent& proprietaire, uint8* noeudMemoire)
{
	ACubeIntelligence* cubeIntelligence = Cast<ACubeIntelligence>(proprietaire.GetAIOwner());

	AProjetMondeVirtuelCharacter* cible = Cast<AProjetMondeVirtuelCharacter>(proprietaire.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(cubeIntelligence->cleCube));

	if (cible)
	{
		// UE_LOG(LogClass, Log, TEXT("Bouge vers ennemi"))
		cubeIntelligence->MoveToActor(cible, 100.f, true, true, true, 0, true);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
