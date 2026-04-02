// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Rifle.h"
#include "TimerManager.h"
#include "Engine/World.h"

ARifle::ARifle()
{
	Damage = 15.0f;
	FireRate = 0.1f; // 10 выстрелов в секунду
	SpreadAngle = 1.0f;
	Range = 2000.0f;
}

void ARifle::Fire()
{
	if (!bCanFire) return;

	
	BurstRemaining = BurstCount;
	BurstFire();
	bCanFire = false;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ARifle::ResetFire, FireRate * BurstCount);
}

void ARifle::BurstFire()
{
	if (BurstRemaining <= 0) return;

	Super::Fire(); 
	BurstRemaining--;
	if (BurstRemaining > 0)
	{
		GetWorldTimerManager().SetTimer(BurstTimerHandle, this, &ARifle::BurstFire, FireRate);
	}
}
