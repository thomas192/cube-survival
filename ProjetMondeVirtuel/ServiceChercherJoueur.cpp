// Fill out your copyright notice in the Description page of Project Settings.

#include "ServiceChercherJoueur.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "ProjetMondeVirtuelCharacter.h"
#include "CubeIntelligence.h"
#include "CubeCharacter.h"

UServiceChercherJoueur::UServiceChercherJoueur()
{
	this->bCreateNodeInstance = true;
}

void UServiceChercherJoueur::TickNode(UBehaviorTreeComponent& proprietaire, uint8* noeudMemoire, float deltaSeconde)
{
	ACubeIntelligence* cubeIntelligence = Cast<ACubeIntelligence>(proprietaire.GetAIOwner());

	if (cubeIntelligence)
	{
		AProjetMondeVirtuelCharacter* cible = Cast<AProjetMondeVirtuelCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (cible)
		{
			// UE_LOG(LogClass, Log, TEXT("Cible trouvee"))
			proprietaire.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(cubeIntelligence->cleCube, cible);
		}
	}
}

