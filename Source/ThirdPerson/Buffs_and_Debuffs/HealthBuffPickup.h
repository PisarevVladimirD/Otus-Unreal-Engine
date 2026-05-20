// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buffs_and_Debuffs/BaseEffectPickup.h"
#include "HealthBuffPickup.generated.h"

/**
 * 
 */
UCLASS()
class AHealthBuffPickup : public ABaseEffectPickup
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect(APlayerCharacter* Character) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff|Health")
	float HealAmount = 30.0f;
};
