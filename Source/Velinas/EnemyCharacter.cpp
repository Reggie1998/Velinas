// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing2"));
	//PawnSensing->SensingInterval = 0.25f;
	//PawnSensing->bOnlySensePlayers = false;
	//PawnSensing->SetPeripheralVisionAngle(35.0f);
	//PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyCharacter::SeePawn);

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AEnemyCharacter::OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume)
{

	const FString VolumeDesc = FString::Printf(TEXT(" at volume %f"), Volume);    
	FString message = TEXT("Heard Actor ") + OtherActor->GetName() + VolumeDesc;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	// TODO: game-specific logic    
}

void AEnemyCharacter::SeePawn(APawn* Pawn)
{
	//Doesn't use this right now
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AAAAAAAAAA"));
	//this->GetCharacterMovement()->MoveTo
}

