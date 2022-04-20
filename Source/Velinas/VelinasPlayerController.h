// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VelinasPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class AVelinasPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVelinasPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	
	
	bool InAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DodgeKeyPressed;
	
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnSetDestinationHold();

	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Input handler for keyboard */
	void OnMovement(float AxisValue, EAxis::Type Axis);
	void OnMoveUp(float AxisValue);
	void OnMoveRight(float AxisValue);

	FTimerHandle DodgeDuration;

	float DodgeCooldown = 0.8f;
	float DodgePressedTime = -0.8f;

	void TimerElapsed();

	void OnJumpPressed();
	void OnJumpReleased();
	void OnDodgePressed();
	void OnDodgeReleased();
	//float DodgeCooldow
	void OnEquip();

private:
	bool bInputPressed; // Input is bring pressed
	bool bFinishedLastDestination;
	FVector LastDestinationClicked;
	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};


