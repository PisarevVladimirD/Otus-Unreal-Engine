// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buffs_and_Debuffs/BaseEffectPickup.h"
#include "Buffs_and_Debuffs/EffectTypes.h"
#include "ShieldBuffPickup.generated.h"

/**
 * 
 */
UCLASS()
class AShieldBuffPickup : public ABaseEffectPickup
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect(APlayerCharacter* Character) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff|Invulnerability")
	float Duration = 5.0f;
};
