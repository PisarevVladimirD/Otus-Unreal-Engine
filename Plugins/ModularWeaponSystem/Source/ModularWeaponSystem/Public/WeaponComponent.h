// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


USTRUCT(BlueprintType)
struct FWeaponModuleData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag SocketTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer AdditionData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier = 1.1f;
	
};

UCLASS(ClassGroup=(Custom), Abstract)
class MODULARWEAPONSYSTEM_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	FWeaponModuleData GetModuleData() const {return  ModuleData;};

private:

	UPROPERTY(EditAnywhere)
	FWeaponModuleData ModuleData;
};

