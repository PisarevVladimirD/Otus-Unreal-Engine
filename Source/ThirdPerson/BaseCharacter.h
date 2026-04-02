// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/Weapon.h"
#include "BaseCharacter.generated.h"


UCLASS()
class THIRDPERSON_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TArray<TSubclassOf<AWeapon>> WeaponClasses; // классы оружия, которые получит персонаж

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 DefaultWeaponIndex = 0; // индекс оружия, экипируемого по умолчанию

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	AWeapon* CurrentWeapon = nullptr;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(int32 Index);
	
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartFire();
	void StopFire();
	void NextWeapon();
	void PrevWeapon();
	
	TArray<AWeapon*> Inventory;

private:
	bool bIsFiring = false;
	void HandleFiring();
	FTimerHandle FireLoopTimerHandle;
};
