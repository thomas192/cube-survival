// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CubeIntelligence.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ACubeCharacter::ACubeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->degats = 50.0f;

	this->mettreAJourVitesseCubeEnnemi(-200.0f);
}


void ACubeCharacter::toucher()
{
	/*
	FActorSpawnParameters parametres;
	parametres.Template = this;
	parametres.Template->SetActorLocation(FVector(2059.0, 0, 236.0));
	// ACubeCharacter* temp = GetWorld()->SpawnActor<class ACubeCharacter>(FVector(2059.0, 0, 236.0), FRotator(0, 0, 0), parametres);
	ACubeCharacter* temp = GetWorld()->SpawnActor<class ACubeCharacter>(GetClass(), parametres);
	if (temp) {
		UE_LOG(LogClass, Log, TEXT("true"))
		temp->SetOwner(GetOwner());
		temp->AIControllerClass = ACubeIntelligence::StaticClass();
		UGameplayStatics::FinishSpawningActor(temp, parametres.Template->GetTransform());
		temp->SpawnDefaultController();
	}
	*/
	this->SetActorLocation(FVector(2059.0, 0, 236.0));
	// Destroy();
}

void ACubeCharacter::mettreAJourVitesseCubeEnnemi(float variationVitesse)
{
	this->GetCharacterMovement()->MaxWalkSpeed += variationVitesse;
}

float ACubeCharacter::getDegats()
{
	return this->degats;
}

// Called when the game starts or when spawned
void ACubeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACubeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

