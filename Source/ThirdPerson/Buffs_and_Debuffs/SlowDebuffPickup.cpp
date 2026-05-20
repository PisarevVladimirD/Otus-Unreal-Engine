// Fill out your copyright notice in the Description page of Project Settings.


#include "Buffs_and_Debuffs/SlowDebuffPickup.h"
#include "PlayerCharacter.h"


void ASlowDebuffPickup::ApplyEffect(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->ApplySlow(SlowRatio, Duration);
	}
}
