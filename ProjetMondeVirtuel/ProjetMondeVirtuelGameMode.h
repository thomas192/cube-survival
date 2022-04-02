// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ProjetMondeVirtuelGameMode.generated.h"

// Différents états de jeu
UENUM(BlueprintType)
enum class EEtatJeu : uint8
{
	EEnJeu,
	EFini,
	EInconnu
};

UCLASS(minimalapi)
class AProjetMondeVirtuelGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	/** Garder trace de l'état de jeu actuel */
	EEtatJeu etatActuel;

	/** Liste qui stocke les volumes d'apparition instanciés */
	TArray<class AApparition*> apparitions;

protected:
	/** Taux de perte de vie du personnage */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vie", Meta = (BlueprintProtected = "true"))
		float tauxPerteVie;

	/** La classe Widget utilisée pour le HUD */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vie", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> classeWidgetHUD;

	/** L'instance du HUD */
	UPROPERTY()
		class UUserWidget* widgetActuel;

	/** Temps écoulé depuis le début du jeu */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Partie", Meta = (AllowPrivateAccess = "true"))
		float tempsEcoule;

	/** Temps écoulé entre le début du jeu et la fin de la mort du joueur */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Partie", Meta = (AllowPrivateAccess = "true"))
		float tempsPartie;

private:
	/** Gère les appels de fonction qui dépendent du changement d'état de jeu */
	void gererNouvelEtat(EEtatJeu nouvelEtat);

public:
	AProjetMondeVirtuelGameMode();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	/** Retourne l'état de jeu actuel */
	UFUNCTION(BlueprintPure, Category = "Cube")
		EEtatJeu getEtatActuel() const;

	UFUNCTION(BlueprintPure, Category = "Partie")
		float getTempsEcoule();

	UFUNCTION(BlueprintPure, Category = "Partie")
		float getTempsPartie();

	/** Définit l'état de jeu actuel */
	void setEtatActuel(EEtatJeu nouvelEtat);
};



