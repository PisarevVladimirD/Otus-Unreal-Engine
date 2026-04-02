// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API ARifle : public AWeapon
{
	GENERATED_BODY()
	
public:
	ARifle();

	virtual void Fire() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int32 BurstCount = 3;

	void BurstFire();
	int32 BurstRemaining;
	FTimerHandle BurstTimerHandle;
};
