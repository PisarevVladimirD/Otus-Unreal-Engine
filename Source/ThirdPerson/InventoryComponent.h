// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item_Pickup_System/WeaponType.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddWeapon(EWeaponType WeaponType, int32 InitialAmmo);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddAmmo(int32 Amount);
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool HasWeapon(EWeaponType WeaponType) const;
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetUniversalAmmo() const { return UniversalAmmo; }
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Inventory")
	void SetUniversalAmmo(int32 NewAmmo);
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	const TSet<EWeaponType>& GetOwnedWeapons() const { return OwnedWeapons; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSet<EWeaponType> OwnedWeapons;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 UniversalAmmo = 0;

private:
	void LogInventoryAction(const FString& Message);
};

