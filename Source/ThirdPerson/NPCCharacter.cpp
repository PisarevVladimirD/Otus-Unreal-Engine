// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "Item_Pickup_System/BasePickup.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "Item_Pickup_System/AmmoPickup.h"
#include "Item_Pickup_System/WeaponPickup.h"

ANPCCharacter::ANPCCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

    CurrentHealth = MaxHealth;
}

void ANPCCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ANPCCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateBehaviour();   
}


void ANPCCharacter::UpdateBehaviour_Implementation()
{

}

void ANPCCharacter::AddPickup_Implementation(ABasePickup* Pickup)
{
    if (!Pickup || !InventoryComponent) return;

    const EItemType Type = Pickup->GetItemType();
    switch (Type)
    {
    case EItemType::Ammo:
        {
            AAmmoPickup* AmmoPickup = Cast<AAmmoPickup>(Pickup);
            if (AmmoPickup)
                InventoryComponent->AddAmmo(AmmoPickup->GetAmmoAmount());
        }
        break;
    case EItemType::Weapon:
        {
            AWeaponPickup* WeaponPickup = Cast<AWeaponPickup>(Pickup);
            if (WeaponPickup)
                InventoryComponent->AddWeapon(WeaponPickup->GetWeaponType(), WeaponPickup->GetInitialAmmo());
        }
        break;
    
    default:
        break;
    }
}

void ANPCCharacter::FireWeapon()
{
    if (!InventoryComponent) return;

    if (InventoryComponent->GetOwnedWeapons().Num() > 0 && InventoryComponent->GetUniversalAmmo() > 0)
    {

        InventoryComponent->SetUniversalAmmo(InventoryComponent->GetUniversalAmmo() - 1);


        FVector Start = GetActorLocation();
        FVector Forward = GetActorForwardVector();
        FVector End = Start + Forward * 10000.0f;

        FHitResult Hit;
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);
        if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
        {

            if (AActor* HitActor = Hit.GetActor())
            {

                UE_LOG(LogTemp, Warning, TEXT("NPC hit %s"), *HitActor->GetName());
            }
        }
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f);
        UE_LOG(LogTemp, Log, TEXT("NPC fired weapon. Ammo left: %d"), InventoryComponent->GetUniversalAmmo());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NPC cannot fire: no weapon or ammo"));
    }
}


void ANPCCharacter::Heal(float Amount)
{
    CurrentHealth = FMath::Min(CurrentHealth + Amount, MaxHealth);
}

void ANPCCharacter::ApplySpeedBuff(float Multiplier, float Duration)
{
    GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed * Multiplier;
    GetWorldTimerManager().ClearTimer(SpeedBuffTimer);
    GetWorldTimerManager().SetTimer(SpeedBuffTimer, this, &ANPCCharacter::ResetSpeed, Duration, false);
}

void ANPCCharacter::ResetSpeed()
{
    GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
}

void ANPCCharacter::ApplyInvulnerability(float Duration)
{
    bInvulnerable = true;
    GetWorldTimerManager().ClearTimer(InvulnerabilityTimer);
    GetWorldTimerManager().SetTimer(InvulnerabilityTimer, this, &ANPCCharacter::DeactivateInvulnerability, Duration, false);
}

void ANPCCharacter::DeactivateInvulnerability()
{
    bInvulnerable = false;
}

void ANPCCharacter::ApplyDamageOverTime(float DPS, float Duration)
{
    GetWorldTimerManager().ClearTimer(DamageTimer);
    FTimerDelegate DamageDelegate;
    DamageDelegate.BindLambda([this, DPS]() { TakeDamage(DPS); });
    GetWorldTimerManager().SetTimer(DamageTimer, DamageDelegate, 1.0f, true);

    FTimerHandle StopHandle;
    GetWorldTimerManager().SetTimer(StopHandle, [this]() {
        GetWorldTimerManager().ClearTimer(DamageTimer);
    }, Duration, false);
}

void ANPCCharacter::ApplySlow(float Ratio, float Duration)
{
    GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed * Ratio;
    GetWorldTimerManager().ClearTimer(SlowTimer);
    GetWorldTimerManager().SetTimer(SlowTimer, this, &ANPCCharacter::ResetSlow, Duration, false);
}

void ANPCCharacter::ResetSlow()
{
    GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
}

void ANPCCharacter::TakeDamage(float Damage)
{
    if (bInvulnerable) return;

    CurrentHealth = FMath::Max(CurrentHealth - Damage, 0.0f);
    if (CurrentHealth <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("NPC %s died"), *GetName());
        Destroy();
    }
}
