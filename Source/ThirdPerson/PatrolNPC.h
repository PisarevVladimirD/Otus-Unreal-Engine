// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCCharacter.h"
#include "PatrolNPC.generated.h"


UCLASS()
class APatrolNPC : public ANPCCharacter
{
	GENERATED_BODY()

public:
	APatrolNPC();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TArray<AActor*> PatrolPoints;


	virtual void UpdateBehaviour_Implementation() override;

private:
	int32 CurrentPointIndex = 0;
	float WaitTimer = 0.0f;
	float WaitTimeAtPoint = 1.0f;
};