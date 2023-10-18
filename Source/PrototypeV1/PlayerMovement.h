// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerMovement.generated.h"

class UCharacterMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROTOTYPEV1_API UPlayerMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerMovement();

	void Initialize(class UCharacterMovementComponent* InCharacterMovement, class UCapsuleComponent* InCapsuleComponent, class AActor* InOwner);

	void MoveVert(float AxisVal);
	void MoveHor(float AxisVal);
	void TurnVert(float AxisVal);
	void TurnHor(float AxisVal);
	void StartSprinting();
	void StopSprinting();
	void StartCrouching();
	void StopCrouching();
	void StartProning();
	void StopProning();

private:
	bool IsSprinting;
	bool IsCrouching;
	bool IsProning;
	float BaseSpeed;
	float SprintSpeedMultiplier;
	float CrouchSpeedMultiplier;
	float ProneSpeedMultiplier;

	UCharacterMovementComponent* CharacterMovement;
	UCapsuleComponent* CapsuleComponent;
	AActor* Owner;
};