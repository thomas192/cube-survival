// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetMondeVirtuelCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Cube.h"
#include "CubeVert.h"
#include "CubeRouge.h"
#include "CubeBleu.h"
#include "CubeCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AProjetMondeVirtuelCharacter

AProjetMondeVirtuelCharacter::AProjetMondeVirtuelCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	
	// Créer la sphère d'attrapage
	this->attrapeur = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere de cueillette"));
	this->attrapeur->AttachTo(this->RootComponent);
	this->attrapeur->SetSphereRadius(200.f);

	// Définir la vie initiale du personnage
	vieInitiale = 100.f;
	viePersonnage = vieInitiale;

	this->nombreCubeVertAttrape = 0;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjetMondeVirtuelCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjetMondeVirtuelCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjetMondeVirtuelCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjetMondeVirtuelCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjetMondeVirtuelCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjetMondeVirtuelCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProjetMondeVirtuelCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AProjetMondeVirtuelCharacter::OnResetVR);

	// Cube
	PlayerInputComponent->BindAction("Attraper", IE_Pressed, this, &AProjetMondeVirtuelCharacter::attraperCube);
}


void AProjetMondeVirtuelCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AProjetMondeVirtuelCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AProjetMondeVirtuelCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AProjetMondeVirtuelCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProjetMondeVirtuelCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AProjetMondeVirtuelCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AProjetMondeVirtuelCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AProjetMondeVirtuelCharacter::attraperCube()
{
	UE_LOG(LogClass, Log, TEXT("AProjetMondeVirtuelCharacter::attraperCube()"))

	// Récupérer les acteurs à l'intérieur de l'attrapeur et les stocker dans une liste
	TArray<AActor*> cubes;
	this->attrapeur->GetOverlappingActors(cubes);

	// Garder trace des bonus collectés
	float vieCollectee = 0;
	float bonusVitesseCollecte = 0;
	float bonusSautCollecte = 0;

	// Pour chaque acteur récupéré vérifier si c'est un cube
	for (int32 position = 0; position < cubes.Num(); position++)
	{
		AActor* acteur = cubes[position];
		ACube* cube = Cast<ACube>(acteur);

		// Si c'est un cube et qu'il est valide et actif
		if (cube && !cube->IsPendingKill() && cube->estActif())
		{
			cube->attraper();
			// Vérifier si le cube est un cube vert
			ACubeVert* const cubeVert = Cast<ACubeVert>(cube);
			if (cubeVert)
			{
				vieCollectee += cubeVert->getBonus();
				this->mettreAJourNombreCubeVertAttrape(1);
			}
			// Vérifier si le cube est un cube rouge
			ACubeRouge* const cubeRouge = Cast<ACubeRouge>(cube);
			if (cubeRouge)
			{
				bonusVitesseCollecte += cubeRouge->getBonus();
			}
			cube->setActif(false);
			// Vérifier si le cube est un cube bleu
			ACubeBleu* const cubeBleu = Cast<ACubeBleu>(cube);
			if (cubeBleu)
			{
				bonusSautCollecte += cubeBleu->getBonus();
			}
			cube->setActif(false);
		}
	}
	// Mise a jour du personnage en fonction des bonus collectés
	if (vieCollectee > 0)
	{
		this->mettreAJourViePersonnage(vieCollectee);
	}
	if (bonusVitesseCollecte > 0)
	{
		this->mettreAJourVitessePersonnage(bonusVitesseCollecte);
	}
	if (bonusSautCollecte > 0)
	{
		this->mettreAJourSautPersonnage(bonusSautCollecte);
	}
}

void AProjetMondeVirtuelCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Récupérer les acteurs à l'intérieur de l'attrapeur et les stocker dans une liste
	TArray<AActor*> cubes;
	this->attrapeur->GetOverlappingActors(cubes);

	// Pour chaque acteur récupéré vérifier si c'est un CubeCharacter
	for (int32 position = 0; position < cubes.Num(); position++)
	{
		AActor* acteur = cubes[position];
		ACubeCharacter* cubeCharacter = Cast<ACubeCharacter>(acteur);
		// Si c'est un CubeCharacter
		if (cubeCharacter)
		{
			UE_LOG(LogClass, Log, TEXT("Touche par le cube ennemi"))
			
			cubeCharacter->toucher();
			this->mettreAJourViePersonnage(-cubeCharacter->getDegats());
		}
	}
}

/** Retourne la vie initiale */
float AProjetMondeVirtuelCharacter::getVieInitiale()
{
	return this->vieInitiale;
}

/** Retourne la vie actuelle du personnage */
float AProjetMondeVirtuelCharacter::getVieActuelle()
{
	return this->viePersonnage;
}

/** Retourne le nombre de cubes verts attrapés */
uint8 AProjetMondeVirtuelCharacter::getNombreCubeVertAttrape()
{
	return this->nombreCubeVertAttrape;
}

/** Met à jour la vie du personnage */
void AProjetMondeVirtuelCharacter::mettreAJourViePersonnage(float variationVie)
{
	if ((this->viePersonnage + variationVie) > this->vieInitiale)
		this->viePersonnage = this->vieInitiale;
	else
		this->viePersonnage = this->viePersonnage + variationVie;
}

/** Met à jour la vitesse du personnage */
void AProjetMondeVirtuelCharacter::mettreAJourVitessePersonnage(float variationVitesse)
{
	this->GetCharacterMovement()->MaxWalkSpeed += variationVitesse;
}

/** Met à jour la vitesse du personnage */
void AProjetMondeVirtuelCharacter::mettreAJourSautPersonnage(float variationSaut)
{
	this->GetCharacterMovement()->JumpZVelocity += variationSaut;
	float temp = this->GetCharacterMovement()->JumpZVelocity;
	UE_LOG(LogClass, Error, TEXT("%f"), temp)
}

/** Met à jour le nombre de cubes verts attrapés */
void AProjetMondeVirtuelCharacter::mettreAJourNombreCubeVertAttrape(uint8 variationNombre)
{
	this->nombreCubeVertAttrape += variationNombre;
}
