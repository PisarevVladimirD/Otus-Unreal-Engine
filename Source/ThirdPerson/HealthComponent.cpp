// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}
void UHealthComponent::TakeDamage(float Damage, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f) return;
	if (CurrentHealth <= 0.0f) return;

	float ActualDamage = FMath::Min(Damage, CurrentHealth);
	CurrentHealth -= ActualDamage;
	

	
	

	if (CurrentHealth <= 0.0f)
	{
		HandleDeath();
	}
}

void UHealthComponent::HandleDeath()
{
	if (bAutoDestroyOnDeath)
	{
		AActor* Owner = GetOwner();
		if (Owner)
		{
			Owner->SetLifeSpan(DestroyDelay);
		}
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

