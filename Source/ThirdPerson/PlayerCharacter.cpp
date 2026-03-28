// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ModularWeaponActor.h"


APlayerCharacter::APlayerCharacter()
{
    PluginInstance = new AModularWeaponActor();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
    
    PlayerInputComponent->BindAction("CallAddFunction", IE_Pressed, this, &APlayerCharacter::CallAddFunction);
    PlayerInputComponent->BindAction("CallRemoveFunction", IE_Pressed, this, &APlayerCharacter::CallRemoveFunction);
    
}
void APlayerCharacter::CallPluginFunctionAdd()
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
}