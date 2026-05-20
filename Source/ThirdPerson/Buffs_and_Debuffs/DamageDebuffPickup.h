// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buffs_and_Debuffs/BaseEffectPickup.h"
#include "Buffs_and_Debuffs/EffectTypes.h"
#include "DamageDebuffPickup.generated.h"

/**
 * 
 */
UCLASS()
class ADamageDebuffPickup : public ABaseEffectPickup
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect(APlayerCharacter* Character) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debuff|Damage")
	float DamagePerSecond = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debuff|Damage")
	float Duration = 5.0f;
};