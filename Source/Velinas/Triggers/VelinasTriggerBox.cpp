// Fill out your copyright notice in the Description page of Project Settings.


#include "Velinas/Triggers/VelinasTriggerBox.h"

#include "Velinas/VelinasCharacter.h"


AVelinasTriggerBox::AVelinasTriggerBox()
{
	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AVelinasTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AVelinasTriggerBox::OnOverlapEnd);
}

void AVelinasTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, 999, 0, 5);
}
void AVelinasTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	//OtherActor->GetInstigatorController()
	// check if Actors do not equal nullptr and that
	if (OtherActor && OtherActor != this) 
	{
		OtherActor->TakeDamage(1.00f, FDamageEvent(), nullptr, this);
		if(AVelinasCharacter* Character = Cast<AVelinasCharacter>(OtherActor))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("AAAAAAA"));
			Character->TakeDamage(5.00f, FDamageEvent(), Character->GetController(), this);
			//Character->
			//Character->GetMesh()->SkeletalMesh->FindSocket(FName("foot_l_Socket"))->AttachActor(Sword, Character->GetMesh());
		}
		//USkeletalMeshSocket *socket = OtherActor->GetMesh()->SkeletalMesh->FindSocket(FName("hand_rSocket"));
		if (GEngine) 
		{ 
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Begin"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Overlapped Actor = %s"), *OverlappedActor->GetName()));
		}
	}
}

void AVelinasTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this) 
	{
		if (GEngine) 
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Ended"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("%s has left the Trigger Box"), *OtherActor->GetName()));
		}
	}
}