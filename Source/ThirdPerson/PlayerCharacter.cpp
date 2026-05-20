// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "HealthComponent.h"
#include "ModularWeaponActor.h"
#include "Item_Pickup_System/BasePickup.h"
#include "Item_Pickup_System/AmmoPickup.h"
#include "Item_Pickup_System/OpticSightPickup.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Item_Pickup_System/WeaponPickup.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"

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
void APlayerCharacter::Heal(float Amount)
{
    HealthComponent->CurrentHealth = FMath::Min(HealthComponent->CurrentHealth + Amount, HealthComponent->MaxHealth);
    UE_LOG(LogTemp, Warning, TEXT("Healed for %f, current health: %f"), Amount, HealthComponent->CurrentHealth);
}

void APlayerCharacter::ApplySpeedBuff(float Multiplier, float Duration)
{
    UCharacterMovementComponent* Movement = GetCharacterMovement();
    if (!Movement) return;

    float NewSpeed = DefaultMaxWalkSpeed * Multiplier;
    Movement->MaxWalkSpeed = NewSpeed;
    
    GetWorldTimerManager().ClearTimer(SpeedBuffTimer);
    GetWorldTimerManager().SetTimer(SpeedBuffTimer, this, &APlayerCharacter::ResetSpeed, Duration, false);

    UE_LOG(LogTemp, Warning, TEXT("Speed buff applied: x%f for %f sec"), Multiplier, Duration);
}
void APlayerCharacter::ResetSpeed()
{
    UCharacterMovementComponent* Movement = GetCharacterMovement();
    if (Movement)
    {
        Movement->MaxWalkSpeed = DefaultMaxWalkSpeed;
    }
    UE_LOG(LogTemp, Warning, TEXT("Speed buff ended"));
}

void APlayerCharacter::ApplyInvulnerability(float Duration)
{
    HealthComponent->bInvulnerable = true;
    
    if (GetWorld())
    {
        GetWorldTimerManager().ClearTimer(InvulnerabilityTimer);
        GetWorldTimerManager().SetTimer(InvulnerabilityTimer, this, &APlayerCharacter::DeactivateInvulnerability, Duration, false);
    }

    UE_LOG(LogTemp, Warning, TEXT("Invulnerability activated for %.1f seconds"), Duration);
}

void APlayerCharacter::DeactivateInvulnerability()
{
    bInvulnerable = false;
    UE_LOG(LogTemp, Warning, TEXT("Invulnerability deactivated"));
}
void APlayerCharacter::ApplyDamageOverTime(float DPS, float Duration)
{
    GetWorldTimerManager().ClearTimer(DamageTimer);
    FTimerDelegate DamageDelegate;
    DamageDelegate.BindLambda([this, DPS]()
    {
        HealthComponent->TakeDamage(DPS);
    });
    GetWorldTimerManager().SetTimer(DamageTimer, DamageDelegate, 1.0f, true); // повторять каждую секунду
    
    FTimerHandle StopHandle;
    GetWorldTimerManager().SetTimer(StopHandle, [this]()
    {
        GetWorldTimerManager().ClearTimer(DamageTimer);
        UE_LOG(LogTemp, Warning, TEXT("Damage over time ended"));
    }, Duration, false);

    UE_LOG(LogTemp, Warning, TEXT("Damage over time applied: %f dps for %f sec"), DPS, Duration);
}

void APlayerCharacter::ApplySlow(float Ratio, float Duration)
{
    UCharacterMovementComponent* Movement = GetCharacterMovement();
    if (!Movement) return;

    float NewSpeed = DefaultMaxWalkSpeed * Ratio;
    Movement->MaxWalkSpeed = NewSpeed;

    GetWorldTimerManager().ClearTimer(SlowTimer);
    GetWorldTimerManager().SetTimer(SlowTimer, this, &APlayerCharacter::ResetSlow, Duration, false);

    UE_LOG(LogTemp, Warning, TEXT("Slow applied: speed x%f for %f sec"), Ratio, Duration);
}

void APlayerCharacter::ResetSlow()
{
    UCharacterMovementComponent* Movement = GetCharacterMovement();
    if (Movement)
    {
        Movement->MaxWalkSpeed = DefaultMaxWalkSpeed;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Slow debuff ended"));
}
