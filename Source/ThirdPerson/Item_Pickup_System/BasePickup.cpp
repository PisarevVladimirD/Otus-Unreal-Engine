// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Pickup_System/BasePickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"

// Sets default values
ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(100.f);
	SphereCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (APlayerCharacter* Char = Cast<APlayerCharacter>(OtherActor))
	{
		PickUp(Char);
	}
}

void ABasePickup::PickUp_Implementation(AActor* Picker)
{
	
	if (APlayerCharacter* Char = Cast<APlayerCharacter>(Picker))
	{
		Char->AddItem(this);
		Destroy();   
	}
}

