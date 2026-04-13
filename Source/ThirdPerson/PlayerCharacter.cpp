// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ModularWeaponActor.h"


APlayerCharacter::APlayerCharacter()
{
    
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
    
    PlayerInputComponent->BindAction("CallAddFunctionPlugin", IE_Pressed, this, &APlayerCharacter::CallAddFunctionPlugin);
    PlayerInputComponent->BindAction("CallRemoveFunctionPlugin", IE_Pressed, this, &APlayerCharacter::CallRemoveFunctionPlugin);
    
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