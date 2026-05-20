// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InventoryWidget.h"
#include "ModularWeaponSystem.h"
#include "ModularWeaponActor.h"
#include "Buffs_and_Debuffs/HealthBuffPickup.h"
#include "Buffs_and_Debuffs/ShieldBuffPickup.h"
#include "Buffs_and_Debuffs/SpeedBuffPickup.h"
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
	
	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable)
	void ApplySpeedBuff(float Multiplier, float Duration);
	void ResetSpeed();

	UFUNCTION(BlueprintCallable)
	void ApplyInvulnerability(float Duration);


	UFUNCTION(BlueprintCallable)
	void DeactivateInvulnerability();
	
	UFUNCTION(BlueprintCallable)
	void ApplyDamageOverTime(float DPS, float Duration);

	UFUNCTION(BlueprintCallable)
	void ApplySlow(float Ratio, float Duration);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float DefaultMaxWalkSpeed = 600.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	bool bInvulnerable = false;
	
	FTimerHandle SpeedBuffTimer;
	FTimerHandle InvulnerabilityTimer;
	FTimerHandle DamageTimer;
	FTimerHandle SlowTimer;
	
	

	
	


	void ApplyDamageTick(float Damage);
	void ResetSlow();
private:
	AModularWeaponActor* PluginInstance; 

	void CallAddFunction(); 
	void CallRemoveFunction();
};

