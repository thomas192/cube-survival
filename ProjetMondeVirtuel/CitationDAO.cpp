// Fill out your copyright notice in the Description page of Project Settings.


#include "CitationDAO.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ACitationDAO::ACitationDAO()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void ACitationDAO::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACitationDAO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACitationDAO::demanderCitation()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> demande = http->CreateRequest();
	demande->OnProcessRequestComplete().BindUObject(this, &ACitationDAO::recevoirCitations);
	demande->SetURL("https://type.fit/api/quotes");
	demande->SetVerb("GET");
	demande->SetHeader("Content-Type", TEXT("application/json"));
	demande->ProcessRequest();
}

void ACitationDAO::recevoirCitations(FHttpRequestPtr demande, FHttpResponsePtr reponse, bool succes)
{
	FString texte = reponse->GetContentAsString();

	TSharedRef<TJsonReader<>> lecteur = TJsonReaderFactory<>::Create(texte);

	TSharedPtr<FJsonValue> json;

	if (FJsonSerializer::Deserialize(lecteur, json))
	{
		TArray<TSharedPtr<FJsonValue>> citations = json->AsArray();
		// Récupérer une citation au hasard
		TSharedPtr<FJsonObject> c = citations[FMath::RandRange(0, citations.Num())]->AsObject();

		this->citation = c->GetStringField("text");
		this->auteur = c->GetStringField("author");

		// UE_LOG(LogClass, Log, TEXT("Citation: %s"), *citation);
		// UE_LOG(LogClass, Log, TEXT("Auteur: %s"), *auteur);

	}
}

FString ACitationDAO::getCitation()
{
	return this->citation;
}

FString ACitationDAO::getAuteur()
{
	return this->auteur;
}



