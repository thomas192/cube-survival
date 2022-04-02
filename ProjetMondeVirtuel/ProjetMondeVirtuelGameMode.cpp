// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetMondeVirtuelGameMode.h"
#include "ProjetMondeVirtuelCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Apparition.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/GameState.h"
#include "CitationDAO.h"


AProjetMondeVirtuelGameMode::AProjetMondeVirtuelGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Taux de perte de vie du personnage
	tauxPerteVie = 0.015f;

	ACitationDAO* citationDAO = CreateDefaultSubobject<ACitationDAO>(TEXT("DAO"));
	citationDAO->demanderCitation();
}

void AProjetMondeVirtuelGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Trouver tous les acteurs de la classe Apparition
	TArray<AActor*> acteursTrouves;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AApparition::StaticClass(), acteursTrouves);

	for (auto acteur : acteursTrouves)
	{
		// On v�rifie que l'acteur est bien une instance de Apparition
		AApparition* acteurApparition = Cast<AApparition>(acteur);
		if (acteurApparition)
		{
			// Ajouter le volume d'apparition � la liste qui les recense
			apparitions.AddUnique(acteurApparition);
		}
	}

	// On est en jeu quand le jeu commence
	setEtatActuel(EEtatJeu::EEnJeu);

	// V�rifier si on utilise le personnage du projet
	AProjetMondeVirtuelCharacter* personnage = Cast<AProjetMondeVirtuelCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (personnage)
	{
		// V�rifier qu'on a bien d�fini la variable classeWidgetHUD
		if (this->classeWidgetHUD != nullptr)
		{
			// Cr�er le widget
			this->widgetActuel = CreateWidget<UUserWidget>(GetWorld(), this->classeWidgetHUD);
			if (this->widgetActuel != nullptr)
			{
				// Ajouter le widget au viewport
				this->widgetActuel->AddToViewport();
			}
		}
	}
}

void AProjetMondeVirtuelGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->tempsEcoule = GetWorld()->GetTimeSeconds();
	// V�rifie si on utilise le personnage du projet
	AProjetMondeVirtuelCharacter* personnage = Cast<AProjetMondeVirtuelCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (personnage && this->getEtatActuel() != EEtatJeu::EFini)
	{
		// Si le personnage a encore de la vie
		if (personnage->getVieActuelle() > 0)
		{
			// R�duit la vie du personnage en utilisant le taux de perte
			personnage->mettreAJourViePersonnage(-DeltaTime * tauxPerteVie * (personnage->getVieInitiale()) * (personnage->getNombreCubeVertAttrape() + 1));
		}
		else
		{
			this->tempsPartie = this->tempsEcoule;
			setEtatActuel(EEtatJeu::EFini);
		}
	}
}

float AProjetMondeVirtuelGameMode::getTempsEcoule()
{
	return this->tempsEcoule;
}

float AProjetMondeVirtuelGameMode::getTempsPartie()
{
	return this->tempsPartie;
}

EEtatJeu AProjetMondeVirtuelGameMode::getEtatActuel() const
{
	return this->etatActuel;
}

void AProjetMondeVirtuelGameMode::setEtatActuel(EEtatJeu nouvelEtat)
{
	// D�finir l'�tat actuel de jeu
	this->etatActuel = nouvelEtat;

	// G�rer le nouvel �tat
	this->gererNouvelEtat(etatActuel);
}

void AProjetMondeVirtuelGameMode::gererNouvelEtat(EEtatJeu nouvelEtat)
{
	switch (nouvelEtat)
	{
		// Si on est en jeu
		case EEtatJeu::EEnJeu:
		{
			// Zone d'apparition actives
			for (AApparition* zone : apparitions)
			{
				zone->setApparitionActive(true);
			}
		}
		break;

		// Si le jeu est fini
		case EEtatJeu::EFini:
		{
			// Zones d'apparition inactives
			for (AApparition* zone : apparitions)
			{
				zone->setApparitionActive(false);
			}
			// Bloque la saisie du joueur
			APlayerController* controleurJoueur = UGameplayStatics::GetPlayerController(this, 0);
			if (controleurJoueur)
			{
				controleurJoueur->SetCinematicMode(true, false, false, true, true);
			}
			// Ragdoll le personnage
			ACharacter* personnage = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (personnage)
			{
				UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.15);
				personnage->GetMesh()->SetSimulatePhysics(true);
				personnage->GetMovementComponent()->MovementState.bCanJump = false;
			}
		}
		break;

		// Inconnu/�tat pra d�faut
		default:
		case EEtatJeu::EInconnu:
		{
			// Ne rien faire
		}
		break;
	}
}
