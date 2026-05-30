// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolNPC.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

APatrolNPC::APatrolNPC()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APatrolNPC::UpdateBehaviour_Implementation()
{
	if (PatrolPoints.Num() == 0) return;

	AActor* TargetPoint = PatrolPoints[CurrentPointIndex];
	if (!TargetPoint) return;
	
	FVector Direction = TargetPoint->GetActorLocation() - GetActorLocation();
	float Distance = Direction.Size();

	if (Distance < 100.0f)
	{

		WaitTimer += GetWorld()->GetDeltaSeconds();
		if (WaitTimer >= WaitTimeAtPoint)
		{
			WaitTimer = 0.0f;
			CurrentPointIndex = (CurrentPointIndex + 1) % PatrolPoints.Num();
		}
	}
	else
	{
		WaitTimer = 0.0f;
		AddMovementInput(Direction.GetSafeNormal());
	}
}
