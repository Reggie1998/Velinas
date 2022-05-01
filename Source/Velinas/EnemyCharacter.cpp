// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Perception//AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetUpStimulus();
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

void AEnemyCharacter::SetUpStimulus()
{
	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();
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

