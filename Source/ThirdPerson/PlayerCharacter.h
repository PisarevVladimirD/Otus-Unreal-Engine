// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "ModularWeaponSystem.h"
#include "ModularWeaponActor.h"
#include "Item_Pickup_System/ItemTypes.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
class ABasePickup;
UCLASS()
class THIRDPERSON_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(ABasePickup* Pickup);
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void CallPluginFunctionAdd();
	void CallPluginFunctionRemove();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<EItemType, int32> InventoryCount;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bHasOpticSight = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	float ScopeMagnification = 0.0f;
private:
	AModularWeaponActor* PluginInstance; 

	void CallAddFunction(); 
	void CallRemoveFunction();
};

