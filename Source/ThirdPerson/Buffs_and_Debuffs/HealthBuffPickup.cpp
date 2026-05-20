// Fill out your copyright notice in the Description page of Project Settings.


#include "Buffs_and_Debuffs/HealthBuffPickup.h"
#include "PlayerCharacter.h"

void AHealthBuffPickup::ApplyEffect(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->Heal(HealAmount);
	}
}