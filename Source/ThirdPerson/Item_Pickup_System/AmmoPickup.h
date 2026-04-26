// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Pickup_System/BasePickup.h"
#include "Item_Pickup_System/ItemTypes.h"
#include "AmmoPickup.generated.h"

UCLASS()
class AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()

public:
	AAmmoPickup();

	virtual EItemType GetItemType() const override { return EItemType::Ammo; }
	int32 GetAmmoAmount() const { return AmmoAmount; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	int32 AmmoAmount = 30;
};