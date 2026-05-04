// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Pickup_System/BasePickup.h"
#include "Item_Pickup_System/WeaponType.h"
#include "WeaponPickup.generated.h"

/**
 * 
 */
UCLASS()
class AWeaponPickup : public ABasePickup
{
	GENERATED_BODY()

public:
	AWeaponPickup();

	virtual EItemType GetItemType() const override { return EItemType::Weapon; }
	EWeaponType GetWeaponType() const { return WeaponType; }
	int32 GetInitialAmmo() const { return InitialAmmo; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType = EWeaponType::Pistol;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 InitialAmmo = 30;
};
