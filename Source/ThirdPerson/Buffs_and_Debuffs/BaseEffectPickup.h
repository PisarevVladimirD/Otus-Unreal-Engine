// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Pickup_System/BasePickup.h"
#include "BaseEffectPickup.generated.h"

/**
 * 
 */
class APlayerCharacter;

UCLASS(Abstract)
class ABaseEffectPickup : public ABasePickup
{
	GENERATED_BODY()

public:
	ABaseEffectPickup();
	
	virtual void ApplyEffect(APlayerCharacter* Character) PURE_VIRTUAL(ABaseEffectPickup::ApplyEffect, );

	virtual void LogPickup(APlayerCharacter* Char);
	virtual void PickUp_Implementation(AActor* Picker) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float RespawnTime = 10.0f;
	
	FTimerHandle RespawnTimerHandle;
	
	void SetPickupActive(bool bActive);
};