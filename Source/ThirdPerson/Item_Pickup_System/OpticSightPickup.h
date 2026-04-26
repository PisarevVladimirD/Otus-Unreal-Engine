// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Pickup_System/BasePickup.h"
#include "Item_Pickup_System/ItemTypes.h"
#include "OpticSightPickup.generated.h"

/**
 * 
 */
UCLASS()
class AOpticSightPickup : public ABasePickup
{
	GENERATED_BODY()

public:
	AOpticSightPickup();

	virtual EItemType GetItemType() const override { return EItemType::OpticSight; }
	float GetMagnification() const { return Magnification; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float Magnification = 4.0f;
};