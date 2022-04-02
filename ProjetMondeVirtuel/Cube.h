// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Cube.generated.h"

UCLASS()
class PROJETMONDEVIRTUEL_API ACube : public AActor
{
	GENERATED_BODY()
private:
	/* Static mesh pour repr�senter le cube dans le niveau */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* mailles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** True quand le cube peut �tre ramass�, et false quand le cube ne peut pas �tre ramass� */
	bool bEstActif;

	/** D�finit le bonus que le cube donne au personnage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cube", meta = (AllowPrivateAccess = "true"))
		float bonus;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	ACube();

	/** Retourne la maille du cube */
	FORCEINLINE class UStaticMeshComponent* getMailles() const { return this->mailles; }

	/** Retourne si le ramassage est activ� ou non */
	UFUNCTION(BlueprintPure, Category = "Cube")
		bool estActif();

	/** Permet � d'autres classes d'activer ou non le ramassage */
	UFUNCTION(BlueprintCallable, Category = "Cube")
		void setActif(bool nouvelEtat);

	/** Retourne le bonus du cube */
	float getBonus();
	
	/** Multiplie le bonus du cube */
	UFUNCTION(BlueprintCallable, Category = "Cube")
		void multiplierBonus(int multiplieur);

	/** Fonction � appeler lorsque le cube est attrap� */
	UFUNCTION(BlueprintNativeEvent)
		void attraper();
	virtual void attraper_Implementation();
};