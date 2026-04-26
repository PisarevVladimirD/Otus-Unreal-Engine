// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "ItemTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemType : uint8
{
	None        UMETA(DisplayName = "None"),
	Ammo        UMETA(DisplayName = "Ammo"),
	OpticSight  UMETA(DisplayName = "Optic Sight")
};
