// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CubeCharacter.generated.h"

UCLASS()
class PROJETMONDEVIRTUEL_API ACubeCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/** Définit les dégats du cube */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CubeCharacter", meta = (AllowPrivateAccess = "true"))
		float degats;

public:
	// Sets default values for this character's properties
	ACubeCharacter();

	/** Fonction à appeler quand le cube ennemi touche le joueur */
	void toucher();

	/** Retourne les dégats du cube */
	float getDegats();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Intelligence")
		class UBehaviorTree* comportement;

	/**
	Met à jour la vitesse du cube ennemi
	* @param variationVitesse Quantité de vitesse dont on va changer la vitesse du cube, peut être positif ou négatif
	*/
	UFUNCTION(BlueprintCallable, Category = "Mouvement")
		void mettreAJourVitesseCubeEnnemi(float variationVitesse);
};
