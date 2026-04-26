// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ModularWeaponActor.h"
#include "Item_Pickup_System/BasePickup.h"
#include "Item_Pickup_System/AmmoPickup.h"
#include "Item_Pickup_System/OpticSightPickup.h"
#include "Engine/Engine.h"

APlayerCharacter::APlayerCharacter()
{
    ///PluginInstance = new AModularWeaponActor();
    PrimaryActorTick.bCanEverTick = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
    
    //PlayerInputComponent->BindAction("CallAddFunction", IE_Pressed, this, &APlayerCharacter::CallAddFunction);
    //PlayerInputComponent->BindAction("CallRemoveFunction", IE_Pressed, this, &APlayerCharacter::CallRemoveFunction);
    
}
/*void APlayerCharacter::CallPluginFunctionAdd()
{
    if (PluginInstance)
    {
        PluginInstance->AddModule(); // Вызываем функцию из плагина
    }
}
void APlayerCharacter::CallPluginFunctionRemove()
{
    if (PluginInstance)
    {
        PluginInstance->RemoveModule(); // Вызываем функцию из плагина
    }
}*/
void APlayerCharacter::AddItem(ABasePickup* Pickup)
{
    if (!Pickup) return;

    const EItemType Type = Pickup->GetItemType();
    FString ItemInfo;

    switch (Type)
    {
    case EItemType::Ammo:
        {
            AAmmoPickup* AmmoPickup = Cast<AAmmoPickup>(Pickup);
            if (AmmoPickup)
            {
                int32 Amount = AmmoPickup->GetAmmoAmount();
                int32& Count = InventoryCount.FindOrAdd(EItemType::Ammo);
                Count += Amount;
                ItemInfo = FString::Printf(TEXT("Picked up Ammo x%d (Total: %d)"), Amount, Count);
            }
        }
        break;

    case EItemType::OpticSight:
        {
            AOpticSightPickup* SightPickup = Cast<AOpticSightPickup>(Pickup);
            if (SightPickup)
            {
                bHasOpticSight = true;
                ScopeMagnification = SightPickup->GetMagnification();
                InventoryCount.FindOrAdd(EItemType::OpticSight) = 1; // условно, считаем что один
                ItemInfo = FString::Printf(TEXT("Picked up Optic Sight (%.1fx)"), ScopeMagnification);
            }
        }
        break;

    default:
        ItemInfo = TEXT("Picked up unknown item");
        break;
    }

    
    UE_LOG(LogTemp, Warning, TEXT("%s"), *ItemInfo);
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, ItemInfo);
    }
}