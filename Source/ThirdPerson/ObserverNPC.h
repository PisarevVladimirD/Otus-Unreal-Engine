// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCCharacter.h"
#include "ObserverNPC.generated.h"

UCLASS()
class AObserverNPC : public ANPCCharacter
{
	GENERATED_BODY()

public:
	AObserverNPC();

	virtual void UpdateBehaviour_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Observe")
	float DetectionRadius = 1500.0f;
};