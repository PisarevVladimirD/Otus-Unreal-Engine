// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Спавн оружия из настроек
    for (TSubclassOf<AWeapon> WeaponClass : WeaponClasses)
    {
        if (WeaponClass)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
            if (Weapon)
            {
                Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
                Weapon->SetOwner(this);
                Inventory.Add(Weapon);
            }
        }
    }

    // Экипируем оружие по умолчанию
    if (Inventory.IsValidIndex(DefaultWeaponIndex))
    {
        EquipWeapon(DefaultWeaponIndex);
    }
}

void ABaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseCharacter::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &ABaseCharacter::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &ABaseCharacter::NextWeapon);
    PlayerInputComponent->BindAction("PrevWeapon", IE_Pressed, this, &ABaseCharacter::PrevWeapon);
}

void ABaseCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ABaseCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}
void ABaseCharacter::StartFire()
{
    if (!bIsFiring && CurrentWeapon)
    {
        bIsFiring = true;
        
        HandleFiring();
        GetWorldTimerManager().SetTimer(FireLoopTimerHandle, this, &ABaseCharacter::HandleFiring, CurrentWeapon->FireRate, true);
    }
}

void ABaseCharacter::StopFire()
{
    bIsFiring = false;
    GetWorldTimerManager().ClearTimer(FireLoopTimerHandle);
}

void ABaseCharacter::HandleFiring()
{
    if (CurrentWeapon && bIsFiring)
    {
        CurrentWeapon->Fire();
    }
}

void ABaseCharacter::EquipWeapon(int32 Index)
{
    if (!Inventory.IsValidIndex(Index)) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->SetActorHiddenInGame(true);
        CurrentWeapon->SetActorEnableCollision(false);
    }

    CurrentWeapon = Inventory[Index];
    CurrentWeapon->SetActorHiddenInGame(false);
    CurrentWeapon->SetActorEnableCollision(true);
}

void ABaseCharacter::NextWeapon()
{
    if (Inventory.Num() == 0) return;
    int32 CurrentIndex = Inventory.Find(CurrentWeapon);
    CurrentWeapon->Destroy();
    int32 NewIndex = (Inventory.Find(CurrentWeapon) + 1) % Inventory.Num();
    EquipWeapon(NewIndex);
}

void ABaseCharacter::PrevWeapon()
{
    if (Inventory.Num() == 0) return;
    int32 CurrentIndex = Inventory.Find(CurrentWeapon);
    CurrentWeapon->Destroy();
    int32 NewIndex = (CurrentIndex - 1 + Inventory.Num()) % Inventory.Num();
    EquipWeapon(NewIndex);
}
float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (HealthComponent)
    {
        HealthComponent->TakeDamage(Damage, EventInstigator, DamageCauser);
    }
    return Damage;
}