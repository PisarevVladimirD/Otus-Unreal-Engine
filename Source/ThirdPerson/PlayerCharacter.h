// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InventoryWidget.h"
#include "ModularWeaponSystem.h"
#include "ModularWeaponActor.h"
#include "Item_Pickup_System/ItemTypes.h"
#include "Item_Pickup_System/WeaponType.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
class ABasePickup;
class UInventoryComponent;
USTRUCT(BlueprintType)
struct FDefaultWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType = EWeaponType::Pistol;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InitialAmmo = 30;
};
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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<EItemType, int32> InventoryCount;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bHasOpticSight = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	float ScopeMagnification = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	UInventoryWidget* InventoryWidgetInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Defaults")
	TArray<FDefaultWeapon> DefaultWeapons;

private:
	AModularWeaponActor* PluginInstance; 

	void CallAddFunction(); 
	void CallRemoveFunction();
};

