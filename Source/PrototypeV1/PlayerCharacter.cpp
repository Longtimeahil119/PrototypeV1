// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerMovement.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMovementComponent = CreateDefaultSubobject<UPlayerMovement>(TEXT("PlayerMovementComponent"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerMovementComponent)
	{
		PlayerMovementComponent->Initialize(GetCharacterMovement(), GetCapsuleComponent(), this);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveVert"), PlayerMovementComponent, &UPlayerMovement::MoveVert);
	PlayerInputComponent->BindAxis(TEXT("MoveHor"), PlayerMovementComponent, &UPlayerMovement::MoveHor);
	PlayerInputComponent->BindAxis(TEXT("TurnHor"), PlayerMovementComponent, &UPlayerMovement::TurnHor);
	PlayerInputComponent->BindAxis(TEXT("TurnVert"), PlayerMovementComponent, &UPlayerMovement::TurnVert);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, PlayerMovementComponent, &UPlayerMovement::StartSprinting);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, PlayerMovementComponent, &UPlayerMovement::StopSprinting);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, PlayerMovementComponent, &UPlayerMovement::StartCrouching);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, PlayerMovementComponent, &UPlayerMovement::StopCrouching);
	PlayerInputComponent->BindAction(TEXT("Prone"), IE_Pressed, PlayerMovementComponent, &UPlayerMovement::StartProning);
	PlayerInputComponent->BindAction(TEXT("Prone"), IE_Released, PlayerMovementComponent, &UPlayerMovement::StopProning);
}
