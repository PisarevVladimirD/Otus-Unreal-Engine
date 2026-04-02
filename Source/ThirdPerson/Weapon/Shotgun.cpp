// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Shotgun.h"

#include "GameFramework/Character.h"

AShotgun::AShotgun()
{
	Damage = 5.0f; // урон на одну дробинку
	FireRate = 1.0f;
	SpreadAngle = 0.0f; // отдельные дробинки имеют свой разброс, общий разброс не нужен
	Range = 800.0f;
}

void AShotgun::Fire()
{
	if (!bCanFire) return;

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());
	if (!PC) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

	for (int32 i = 0; i < PelletCount; ++i)
	{
		FVector ShotDirection = CameraRotation.Vector();
		// добавляем случайное отклонение для каждой дробинки
		float HalfRad = FMath::DegreesToRadians(PelletSpread * 0.5f);
		ShotDirection = FMath::VRandCone(CameraRotation.Vector(), HalfRad);

		PerformLineTrace(CameraLocation, ShotDirection, 0.0f);
	}

	bCanFire = false;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AWeapon::ResetFire, FireRate);
}