// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ModularWeaponActor.h"
#include "Item_Pickup_System/BasePickup.h"
#include "Item_Pickup_System/AmmoPickup.h"
#include "Item_Pickup_System/OpticSightPickup.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Item_Pickup_System/WeaponPickup.h"
#include "Engine/Engine.h"

APlayerCharacter::APlayerCharacter()
{
    ///PluginInstance = new AModularWeaponActor();
    PrimaryActorTick.bCanEverTick = false;
    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
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
void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (InventoryWidgetClass && InventoryComponent)
    {
        InventoryWidgetInstance = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
        if (InventoryWidgetInstance)
        {
            InventoryWidgetInstance->InitializeWidget(InventoryComponent);
            InventoryWidgetInstance->AddToViewport();
        }
    }
    if (InventoryComponent)
    {
        {
            InventoryComponent->AddWeapon(EWeaponType::Pistol, 30);
            InventoryComponent->AddWeapon(EWeaponType::Rifle, 20);
            InventoryComponent->AddWeapon(EWeaponType::Shotgun, 8);
        }
    }
    if (IsLocallyControlled() && InventoryWidgetClass && InventoryComponent)
    {
        InventoryWidgetInstance = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
        if (InventoryWidgetInstance)
        {
            InventoryWidgetInstance->InitializeWidget(InventoryComponent);
            InventoryWidgetInstance->AddToViewport(0); 
        }
    }
}
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
                InventoryComponent->AddAmmo(AmmoPickup->GetAmmoAmount());
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
    case EItemType::Weapon:
        {
            AWeaponPickup* WeaponPickup = Cast<AWeaponPickup>(Pickup);
            if (WeaponPickup)
            {
                InventoryComponent->AddWeapon(WeaponPickup->GetWeaponType(), WeaponPickup->GetInitialAmmo());
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