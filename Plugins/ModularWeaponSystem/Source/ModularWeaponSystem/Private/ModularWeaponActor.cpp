// Fill out your copyright notice in the Description page of Project Settings.
#include "ModularWeaponActor.h"

#include "ModularWeaponSystem.h"
#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AModularWeaponActor::AModularWeaponActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RiflMesh(TEXT("/Game/Weapons/Rifle/Meshes/SM_Rifle.SM_Rifle"));
	if (RiflMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(RiflMesh.Object);
	}
}

// Called when the game starts or when spawned
void AModularWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModularWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AModularWeaponActor::AddModule(TSubclassOf<UWeaponComponent> ModuleClass)
{
	if (!ModuleClass.Get())
	{
		return;
	}
	
	FGameplayTag ModuleSocket = ModuleClass.Get()->GetDefaultObject<UWeaponComponent>()->GetModuleData().SocketTag;

	if (!Sockets.Contains(ModuleSocket))
	{
		return;
	}

	RemoveModule(ModuleSocket);

	FTransform SocketTransform = FTransform::Identity;

	SocketTransform = StaticMesh->GetSocketTransform(Sockets[ModuleSocket], RTS_Actor);

	UWeaponComponent* Component = Cast<UWeaponComponent>(AddComponentByClass(ModuleClass, true, SocketTransform, false));
	if (Component)
	{
		Modules.Add(ModuleSocket, Component);
		Component->AttachToComponent(StaticMesh, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void AModularWeaponActor::RemoveModule(const FGameplayTag Module)
{
	if (!Modules.Contains(Module))
	{
		return;
	}
	
	if (UWeaponComponent* WeaponComponent = *Modules.Find(Module))
	{
		WeaponComponent->DestroyComponent();
		Modules.Remove(Module);
	}
}

float AModularWeaponActor::GetSummaryDamage() const
{
	//TArray<FGameplayTag> Tags;

	float Damage = BaseDamage;
	for (const TPair<FGameplayTag, UWeaponComponent*> Pair : Modules)
	{
		if (Pair.Value)
		{
			Damage *= Pair.Value->GetModuleData().DamageMultiplier;
		}
	}

	return Damage;
}

void AModularWeaponActor::Shot(FVector ShotLocation)
{
	if (!Sockets.Contains(ShotSocket))
	{
		return;
	}
	
	FTransform SocketTransform = FTransform::Identity;
	SocketTransform = StaticMesh->GetSocketTransform(Sockets[ShotSocket]);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, SocketTransform.GetLocation(), ShotLocation + (ShotLocation - SocketTransform.GetLocation()).GetSafeNormal() * 100, ECC_Visibility))
	{
		UGameplayStatics::ApplyDamage(Hit.GetActor(), GetSummaryDamage(), nullptr, nullptr, nullptr);
	}
}

