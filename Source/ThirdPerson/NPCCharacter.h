// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickupableCharacter.h"
#include "InventoryComponent.h"
#include "Item_Pickup_System/WeaponType.h"
#include "NPCCharacter.generated.h"

UCLASS()
class ANPCCharacter : public ACharacter, public IPickupableCharacter
{
	GENERATED_BODY()

public:
	ANPCCharacter();


	virtual void AddPickup_Implementation(ABasePickup* Pickup) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void FireWeapon();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float DefaultMaxWalkSpeed = 600.0f;

	
	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable)
	void ApplySpeedBuff(float Multiplier, float Duration);

	UFUNCTION(BlueprintCallable)
	void ApplyInvulnerability(float Duration);

	UFUNCTION(BlueprintCallable)
	void ApplyDamageOverTime(float DPS, float Duration);

	UFUNCTION(BlueprintCallable)
	void ApplySlow(float Ratio, float Duration);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);


	UFUNCTION(BlueprintNativeEvent, Category = "AI")
	void UpdateBehaviour();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


	bool bInvulnerable = false;
	FTimerHandle InvulnerabilityTimer;
	FTimerHandle SpeedBuffTimer;
	FTimerHandle DamageTimer;
	FTimerHandle SlowTimer;

	void ResetSpeed();
	void DeactivateInvulnerability();
	void ApplyDamageTick(float DPS);
	void ResetSlow();
};