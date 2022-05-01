// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIControllerBase.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackBoard_keys.h"

UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get AI controller and its NPC
	auto const Ctrl = Cast<AAIController>(OwnerComp.GetAIOwner());
	auto const Npc = Ctrl->GetPawn();

	// obtain npc location to use as origin location	
	FVector const Origin = Npc->GetActorLocation();
	FNavLocation Location;

	// get the navigation system and generate a random location on the NavMesh
	UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location, nullptr))
	{
		Ctrl->GetBlackboardComponent()->SetValueAsVector(bb_keys::target_location, Location.Location);
	}

	// finish with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
}
