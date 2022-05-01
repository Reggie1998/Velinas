// Fill out your copyright notice in the Description page of Project Settings.

#include "FindPlayerLocation.h"
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIControllerBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BlackBoard_keys.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get player character and the NPC's controller
	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const Ctrl = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());

	//get player location to use as an origin
	FVector const PlayerLocation = Player->GetActorLocation();
	if (SearchRandom)
	{
		FNavLocation Loc;
		// get the navigation system and generate a random location near the player
		UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (NavSys->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Loc, nullptr))
		{
			Ctrl->GetBlackboard()->SetValueAsVector(bb_keys::target_location, Loc.Location);
		}
	}
	else
	{
		Ctrl->GetBlackboard()->SetValueAsVector(bb_keys::target_location, PlayerLocation);
	}

	//finish with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Type();
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
}
