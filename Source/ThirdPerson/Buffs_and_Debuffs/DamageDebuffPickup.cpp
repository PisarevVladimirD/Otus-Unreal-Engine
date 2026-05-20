// Fill out your copyright notice in the Description page of Project Settings.


#include "Buffs_and_Debuffs/DamageDebuffPickup.h"
#include "PlayerCharacter.h"

void ADamageDebuffPickup::ApplyEffect(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->ApplyDamageOverTime(DamagePerSecond, Duration);
	}
}