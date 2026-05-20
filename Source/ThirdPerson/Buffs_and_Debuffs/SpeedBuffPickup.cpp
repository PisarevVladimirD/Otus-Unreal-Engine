// Fill out your copyright notice in the Description page of Project Settings.


#include "Buffs_and_Debuffs/SpeedBuffPickup.h"
#include "PlayerCharacter.h"

void ASpeedBuffPickup::ApplyEffect(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->ApplySpeedBuff(SpeedMultiplier, Duration);
	}
}
