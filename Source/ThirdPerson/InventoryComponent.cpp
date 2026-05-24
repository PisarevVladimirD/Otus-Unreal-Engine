// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInventoryComponent::AddWeapon(EWeaponType WeaponType, int32 InitialAmmo)
{
	if (WeaponType == EWeaponType::None) return;

	OwnedWeapons.Add(WeaponType);

	UniversalAmmo += InitialAmmo;

	FString Msg = FString::Printf(TEXT("Added weapon: %s with %d ammo (Total: %d)"),
		*UEnum::GetValueAsString(WeaponType), InitialAmmo, UniversalAmmo);
	LogInventoryAction(Msg);

	OnInventoryChanged.Broadcast();
}

void UInventoryComponent::AddAmmo(int32 Amount)
{
	if (Amount <= 0) return;
	UniversalAmmo += Amount;

	FString Msg = FString::Printf(TEXT("Added %d universal ammo (Total: %d)"), Amount, UniversalAmmo);
	LogInventoryAction(Msg);

	OnInventoryChanged.Broadcast();
}

bool UInventoryComponent::HasWeapon(EWeaponType WeaponType) const
{
	return OwnedWeapons.Contains(WeaponType);
}

void UInventoryComponent::SetUniversalAmmo(int32 NewAmmo)
{
	NewAmmo = FMath::Max(0, NewAmmo);
	if (UniversalAmmo != NewAmmo)
	{
		UniversalAmmo = NewAmmo;
        
		FString Msg = FString::Printf(TEXT("Universal ammo set to %d"), UniversalAmmo);
		LogInventoryAction(Msg);

		OnInventoryChanged.Broadcast();
	}
}

void UInventoryComponent::LogInventoryAction(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, Message);
	}
}