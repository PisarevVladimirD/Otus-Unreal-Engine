// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupableCharacter.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UPickupableCharacter : public UInterface
{
	GENERATED_BODY()
};

class IPickupableCharacter
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pickup")
	void AddPickup(ABasePickup* Pickup);
};

