// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"
#include "EnemyCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "BlackBoard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"


AAIControllerBase::AAIControllerBase(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/TopDown/AI_v2/BT_Enemy.BT_Enemy'"));
	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}
	BehaviorTreeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	Blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	SetUpPerceptionSystem();
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void AAIControllerBase::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if (Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent* AAIControllerBase::GetBlackboard() const
{
	return Blackboard;
}

void AAIControllerBase::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DETECTED"));
	GetBlackboard()->SetValueAsBool(bb_keys::can_see_player, Stimulus.WasSuccessfullySensed());
	if (auto const Char = Cast<AEnemyCharacter>(Actor))
	{
		GetBlackboard()->SetValueAsBool(bb_keys::can_see_player, Stimulus.WasSuccessfullySensed());
	}
}

void AAIControllerBase::OnUpdated(TArray<AActor*> const& UpdatedActor)
{
	GetBlackboard()->SetValueAsBool(bb_keys::can_see_player, true);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DETECTED"));
}

void AAIControllerBase::SetUpPerceptionSystem()
{
	//create and initialise sight configuration object
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	SightConfig->SightRadius = 500.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies =  true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// add sight configuration component to perception component
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAIControllerBase::OnUpdated);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}
