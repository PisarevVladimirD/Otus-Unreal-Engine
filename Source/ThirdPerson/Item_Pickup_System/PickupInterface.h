// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

class IPickupInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pickup")
	void PickUp(AActor* Picker);
};
/**
 * 
 */

