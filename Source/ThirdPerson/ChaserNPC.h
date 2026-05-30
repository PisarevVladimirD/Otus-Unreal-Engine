// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCCharacter.h"
#include "ChaserNPC.generated.h"

UCLASS()
class AChaserNPC : public ANPCCharacter
{
	GENERATED_BODY()

public:
	AChaserNPC();

	virtual void UpdateBehaviour_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chase")
	float DetectionRadius = 1000.0f;

private:
	ACharacter* FindPlayer() const;
};
