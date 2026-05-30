// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaserNPC.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

AChaserNPC::AChaserNPC()
{
	PrimaryActorTick.bCanEverTick = true;
}

ACharacter* AChaserNPC::FindPlayer() const
{
	return UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AChaserNPC::UpdateBehaviour_Implementation()
{
	ACharacter* Player = FindPlayer();
	if (!Player) return;

	float Dist = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
	if (Dist <= DetectionRadius)
	{

		FVector Dir = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		AddMovementInput(Dir);


		if (Dist < 500.0f && InventoryComponent->GetUniversalAmmo() > 0)
		{
			FireWeapon();
		}
	}
}