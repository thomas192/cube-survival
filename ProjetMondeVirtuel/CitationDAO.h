// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CitationDAO.generated.h"

UCLASS()
class PROJETMONDEVIRTUEL_API ACitationDAO : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACitationDAO();
	FHttpModule* http;

	UFUNCTION(BlueprintPure, Category = "Citation")
		FString getCitation();

	UFUNCTION(BlueprintPure, Category = "Citation")
		FString getAuteur();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FString citation;
	FString auteur;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Fait la requête à l'API */
	void demanderCitation();

	/** Appelée quand la requête à l'API a été effectuée avec succès */
	void recevoirCitations(FHttpRequestPtr demande, FHttpResponsePtr reponse, bool succes);
};
