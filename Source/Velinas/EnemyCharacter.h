// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class VELINAS_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	TWeakObjectPtr<class UPawnSensingComponent> PawnSensing;
	
	//////////////////////////////////////////////////////////////////////////
	// UPawnSensingComponent Delegates

	UFUNCTION()
	void OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume);

	UFUNCTION()
	void SeePawn(APawn *OtherPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
