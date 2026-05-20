// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buffs_and_Debuffs/BaseEffectPickup.h"
#include "Buffs_and_Debuffs/EffectTypes.h"
#include "SlowDebuffPickup.generated.h"

/**
 * 
 */
UCLASS()
class ASlowDebuffPickup : public ABaseEffectPickup
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect(APlayerCharacter* Character) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debuff|Slow")
	float SlowRatio = 0.5f;   

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debuff|Slow")
	float Duration = 4.0f;
};