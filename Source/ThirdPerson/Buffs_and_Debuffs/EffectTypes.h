// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "EffectTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBuffType : uint8
{
	None    UMETA(DisplayName = "None"),
	Health  UMETA(DisplayName = "Health Restore"),
	Speed   UMETA(DisplayName = "Speed Boost"),
	Shield  UMETA(DisplayName = "Shield")
};
