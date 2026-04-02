// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API AShotgun : public AWeapon
{
	GENERATED_BODY()
	
public:
	AShotgun();

	virtual void Fire() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int32 PelletCount = 8;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float PelletSpread = 10.0f;
};
