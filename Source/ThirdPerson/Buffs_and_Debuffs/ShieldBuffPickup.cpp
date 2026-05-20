// Fill out your copyright notice in the Description page of Project Settings.


#include "Buffs_and_Debuffs/ShieldBuffPickup.h"
#include "PlayerCharacter.h"

void AShieldBuffPickup::ApplyEffect(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->ApplyInvulnerability(Duration);
	}
}

