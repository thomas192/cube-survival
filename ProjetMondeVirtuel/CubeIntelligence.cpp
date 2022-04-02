// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeIntelligence.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "CubeCharacter.h"

ACubeIntelligence::ACubeIntelligence()
{
	this->tableauNoir = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Tableau noir"));
	this->comportement = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Comportement"));
}

void ACubeIntelligence::OnPossess(APawn* pion) 
{
	Super::OnPossess(pion);
	
	ACubeCharacter* cube = Cast<ACubeCharacter>(pion);
	if (cube)
	{
		// Récupérer la cible
		this->tableauNoir->InitializeBlackboard(*(cube->comportement->BlackboardAsset));
		this->cleCube = this->tableauNoir->GetKeyID(TEXT("cible"));
		// Démarrer le behavior tree
		this->comportement->StartTree(*(cube->comportement));
	}
}
