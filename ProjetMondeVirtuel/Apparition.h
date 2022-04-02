// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Cube.h"
#include "Apparition.generated.h"

UCLASS()
class PROJETMONDEVIRTUEL_API AApparition : public AActor
{
	GENERATED_BODY()

private:
	/* Box component pour sp�cifier ou les cubes apparaitront */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Apparition", meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* zone;

	/* G�rer l'apparition des cubes */
	void apparaitre();

	/* D�lais d'apparition actuel */
	float delaiApparition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Les cubes � faire apparaitre */
	UPROPERTY(EditAnywhere, Category = "Apparition")
		TSubclassOf<class ACube> objetCubeBleu;
	UPROPERTY(EditAnywhere, Category = "Apparition")
		TSubclassOf<class ACube> objetCubeRouge;
	UPROPERTY(EditAnywhere, Category = "Apparition")
		TSubclassOf<class ACube> objetCubeVert;

	FTimerHandle minuteur;

	/* D�lai d'apparition minimum */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apparition")
		float delaiApparitionMinimum;

	/* D�lai d'apparition maximum */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apparition")
		float delaiApparitionMaximum;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AApparition();

	/* Retourne le subobject zone */
	FORCEINLINE class UBoxComponent* getZone() const { return this->zone; }

	/* G�n�re un point au hasard dans le volume d'apparition */
	UFUNCTION(BlueprintPure, Category = "Apparition")
		FVector getPointsAuHasard();

	/** Active ou d�sactive l'apparition */
	UFUNCTION(BlueprintCallable, Category = "Apparition")
		void setApparitionActive(bool bDevraitApparaitre);
};
