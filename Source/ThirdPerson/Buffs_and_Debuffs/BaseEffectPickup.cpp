// Fill out your copyright notice in the Description page of Project Settings.


#include "Buffs_and_Debuffs/BaseEffectPickup.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"

ABaseEffectPickup::ABaseEffectPickup()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseEffectPickup::PickUp_Implementation(AActor* Picker)
{
	if (APlayerCharacter* Char = Cast<APlayerCharacter>(Picker))
	{
		ApplyEffect(Char);
		LogPickup(Char);
		SetPickupActive(false);
		
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, [this]()
		{
			SetPickupActive(true);
		}, RespawnTime, false);
	}
}

void ABaseEffectPickup::SetPickupActive(bool bActive)
{
	RootComponent->SetVisibility(bActive, true);
	SetActorEnableCollision(bActive);
	SetActorHiddenInGame(!bActive);
	
	if (SphereCollision) SphereCollision->SetActive(bActive);
	if (Mesh) Mesh->SetVisibility(bActive);
}

void ABaseEffectPickup::LogPickup(APlayerCharacter* Char)
{
	FString Msg = FString::Printf(TEXT("Picked up effect: %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Msg);
}
