// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ModularWeaponActor.h"
#include "TestModule/ModuleTestActor.h"


APlayerCharacter::APlayerCharacter()
{
    
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
    
    //PlayerInputComponent->BindAction("CallAddFunctionPlugin", IE_Pressed, this, &APlayerCharacter::CallAddFunctionPlugin);
    //PlayerInputComponent->BindAction("CallRemoveFunctionPlugin", IE_Pressed, this, &APlayerCharacter::CallRemoveFunctionPlugin);
    PlayerInputComponent->BindAction("SpawnModuleTestActor", IE_Pressed, this, &APlayerCharacter::SpawnModuleTestActor);
    PlayerInputComponent->BindAction("SpawnPluginTestActor", IE_Pressed, this, &APlayerCharacter::SpawnPluginTestActor);
}
FVector APlayerCharacter::GetSpawnLocationInFrontOfCharacter(float Distance) const
{
    if (!GetWorld())
    {
        return FVector::ZeroVector;
    }

    FVector ForwardVector = GetActorForwardVector();

    return GetActorLocation() + (ForwardVector * Distance);
}
void APlayerCharacter::SpawnModuleTestActor()
{
    if (UWorld* World = GetWorld())
    {
        FVector SpawnLocation = GetSpawnLocationInFrontOfCharacter();
        FRotator SpawnRotation = GetActorRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        
        AModuleTestActor* SpawnedActor = World->SpawnActor<AModuleTestActor>(AModuleTestActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
    }
}
void APlayerCharacter::SpawnPluginTestActor()
{
    if (UWorld* World = GetWorld())
    {
        FVector SpawnLocation = GetSpawnLocationInFrontOfCharacter();
        FRotator SpawnRotation = GetActorRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        
        AModularWeaponActor* SpawnedActor = World->SpawnActor<AModularWeaponActor>(AModularWeaponActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
    }
}