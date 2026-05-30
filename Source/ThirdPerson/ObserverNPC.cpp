// Fill out your copyright notice in the Description page of Project Settings.


#include "ObserverNPC.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

AObserverNPC::AObserverNPC()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AObserverNPC::UpdateBehaviour_Implementation()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return;

	float Dist = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
	if (Dist <= DetectionRadius)
	{

		FVector Dir = Player->GetActorLocation() - GetActorLocation();
		Dir.Z = 0;
		FRotator LookAt = Dir.Rotation();
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAt, GetWorld()->GetDeltaSeconds(), 5.0f));
		
		if (Dist < 800.0f && InventoryComponent->GetUniversalAmmo() > 0)
		{
			FireWeapon();
		}
	}
}
