// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buffs_and_Debuffs/BaseEffectPickup.h"
#include "Buffs_and_Debuffs/EffectTypes.h"
#include "SpeedBuffPickup.generated.h"

/**
 * 
 */
UCLASS()
class ASpeedBuffPickup : public ABaseEffectPickup
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect(APlayerCharacter* Character) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff|Speed")
	float SpeedMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff|Speed")
	float Duration = 8.0f;
};