// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class VELINAS_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const InPawn) override;
	class UBlackboardComponent* GetBlackboard() const;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackboardComponent;

	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnUpdated(TArray<AActor*> const& UpdatedActor);

	void SetUpPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

};
