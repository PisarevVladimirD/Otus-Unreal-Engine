// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class THIRDPERSON_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float FireRate = 0.5f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float Range = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float SpreadAngle = 0.0f;
	
	FTimerHandle FireTimerHandle;
	bool bCanFire = true;
	
	void PerformLineTrace(const FVector& Start, const FVector& Direction, float ConeAngle);
	void ApplyDamage(AActor* HitActor, const FVector& HitLocation);
	void ResetFire();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
