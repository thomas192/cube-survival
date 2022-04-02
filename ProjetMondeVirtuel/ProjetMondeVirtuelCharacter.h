// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "ProjetMondeVirtuelCharacter.generated.h"

UCLASS(config=Game)
class AProjetMondeVirtuelCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/* Sphere d'attrapage */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* attrapeur;

private:
	/** Vie actuelle du personnage */
	UPROPERTY(VisibleAnywhere, Category = "Vie")
		float viePersonnage;

protected:
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

public:
	AProjetMondeVirtuelCharacter();

	virtual void Tick(float DeltaSeconds) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	/** Appel� lorsque le joueur presse une touche pour attraper les cubes � l'int�rieur de l'attrapeur */
	UFUNCTION(BlueprintCallable, Category = "Cube")
		void attraperCube();

	/** Vie de d�part du personnage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vie")
		float vieInitiale;

	/** Nombre de cubes verts attrap�s */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vie", meta = (AllowPrivateAccess = "true"))
		uint8 nombreCubeVertAttrape;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Retourne le subobject attrapeur **/
	FORCEINLINE class USphereComponent* getAttrapeur() const { return this->attrapeur; }

	/** Accesseur de la vie initiale */
	UFUNCTION(BlueprintPure, Category = "Vie")
		float getVieInitiale();

	/** Accesseur de la vie actuelle du personnage */
	UFUNCTION(BlueprintPure, Category = "Vie")
		float getVieActuelle();

	/** Retourne le nombre de cubes verts attrap�s */
	UFUNCTION(BlueprintPure, Category = "Vie")
		uint8 getNombreCubeVertAttrape();

	/**
	Met � jour la vie du personnage
	* @param variationVie Quantit� de vie dont on va changer la vie du personnage, peut �tre positif ou n�gatif
	*/
	UFUNCTION(BlueprintCallable, Category = "Vie")
		void mettreAJourViePersonnage(float variationVie);

	/**
	Met � jour la vitesse du personnage
	* @param variationVitesse Quantit� de vitesse dont on va changer la vitesse du personnage, peut �tre positif ou n�gatif
	*/
	UFUNCTION(BlueprintCallable, Category = "Mouvement")
		void mettreAJourVitessePersonnage(float variationVitesse);

	/**
	Met � jour la hauteur de saut du personnage
	* @param variationSaut Quantit� de vitesse dont on va changer la hauteur de saut du personnage, peut �tre positif ou n�gatif
	*/
	UFUNCTION(BlueprintCallable, Category = "Mouvement")
		void mettreAJourSautPersonnage(float variationSaut);

	/** Met � jour le nombre de cubes verts attrap�s */
	UFUNCTION(BlueprintCallable, Category = "Vie")
		void mettreAJourNombreCubeVertAttrape(uint8 variationNombre);
};

