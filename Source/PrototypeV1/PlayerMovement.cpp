// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

void UPlayerMovement::Initialize(UCharacterMovementComponent* InCharacterMovement, UCapsuleComponent* InCapsuleComponent, AActor* InOwner)
{
	CharacterMovement = InCharacterMovement;
	CapsuleComponent = InCapsuleComponent;
	Owner = InOwner;
}

UPlayerMovement::UPlayerMovement() 
{
	BaseSpeed = 600.f;

	IsSprinting = false;
	SprintSpeedMultiplier = 1.5f;

	IsCrouching = false;
	CrouchSpeedMultiplier = 0.75f;

	IsProning = false;
	ProneSpeedMultiplier = 0.30f;

	if (CapsuleComponent)
	{
		CapsuleComponent->SetCapsuleHalfHeight(88.0f);
	}
}

void UPlayerMovement::MoveVert(float AxisVal)
{
	
	if (CharacterMovement) 
	{
		CharacterMovement->AddInputVector(GetOwner()->GetActorForwardVector() * AxisVal);
	}
	UE_LOG(LogTemp, Warning, TEXT("Vertical Speed: %f"), AxisVal);
}

void UPlayerMovement::MoveHor(float AxisVal)
{

	if (CharacterMovement)
	{
		CharacterMovement->AddInputVector(GetOwner()->GetActorRightVector() * AxisVal);
	}
}

void UPlayerMovement::TurnVert(float AxisVal)
{
	FRotator NewRotation = GetOwner()->GetActorRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + AxisVal, -89.0f, 89.0f);
	GetOwner()->SetActorRotation(NewRotation);
}

void UPlayerMovement::TurnHor(float AxisVal)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		PlayerController->AddYawInput(AxisVal);
	}
}

void UPlayerMovement::StartSprinting()
{
	IsSprinting = true;
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = BaseSpeed * SprintSpeedMultiplier;
	}
}

void UPlayerMovement::StopSprinting()
{
	IsSprinting = false;
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = BaseSpeed;
	}
}

void UPlayerMovement::StartCrouching()
{
	IsCrouching = true;
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = BaseSpeed * CrouchSpeedMultiplier;
	}

	if (CapsuleComponent)
	{
		CapsuleComponent->SetCapsuleHalfHeight(44.0f);
	}
}

void UPlayerMovement::StopCrouching()
{
	IsCrouching = false;
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = BaseSpeed;
	}

	if (CharacterMovement)
	{
		CapsuleComponent->SetCapsuleHalfHeight(88.0f);
	}
}

void UPlayerMovement::StartProning()
{
	IsProning = true;
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = BaseSpeed * ProneSpeedMultiplier;
	}
	
	if (CapsuleComponent)
	{
		FVector NewLocation = GetOwner()->GetActorLocation();
		NewLocation.Z -= 11.0f;
		CapsuleComponent->SetCapsuleSize(11.0f, 11.0f);
		CapsuleComponent->SetWorldLocation(NewLocation);
	}

}

void UPlayerMovement::StopProning()
{
	IsProning = false;
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = BaseSpeed;
	}

	if (CapsuleComponent)
	{
		FVector NewLocation = GetOwner()->GetActorLocation();
		NewLocation.Z += 11.0f;
		CapsuleComponent->SetCapsuleSize(11.0f, 88.0f);
		CapsuleComponent->SetWorldLocation(NewLocation);
	}

}