// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "WeaponType.generated.h"


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None    UMETA(DisplayName = "None"),
	Pistol  UMETA(DisplayName = "Pistol"),
	Rifle   UMETA(DisplayName = "Rifle"),
	Shotgun   UMETA(DisplayName = "Shotgun")
};
