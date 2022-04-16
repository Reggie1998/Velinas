// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "VelinasTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class VELINAS_API AVelinasTriggerBox : public ATriggerBox
{
GENERATED_BODY()

	public:

	AVelinasTriggerBox();
		
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Sword")
	AActor* Sword;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
