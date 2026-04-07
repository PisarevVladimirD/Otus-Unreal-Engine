// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "HealthComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	bCanFire = true;
}

void AWeapon::Fire()
{
	if (!bCanFire) return;
	
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());
	if (!PC) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

	PerformLineTrace(CameraLocation, CameraRotation.Vector(), SpreadAngle);

	bCanFire = false;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AWeapon::ResetFire, FireRate);
}
void AWeapon::PerformLineTrace(const FVector& Start, const FVector& Direction, float ConeAngle)
{
	FVector ShotDirection = Direction;
	if (ConeAngle > 0.0f)
	{
		
		float HalfRad = FMath::DegreesToRadians(ConeAngle * 0.5f);
		ShotDirection = FMath::VRandCone(Direction, HalfRad);
	}

	FVector End = Start + ShotDirection * Range;
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		DrawDebugLine(GetWorld(), Start, Hit.Location, FColor::Red, false, 2.0f);
		ApplyDamage(Hit.GetActor(), Hit.Location);
	}
	else
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);
	}
}

void AWeapon::ApplyDamage(AActor* HitActor, const FVector& HitLocation)
{
	if (HitActor)
	{
		UHealthComponent* HealthComp = HitActor->FindComponentByClass<UHealthComponent>();
		if (HealthComp)
		{
			HealthComp->TakeDamage(Damage, Cast<AController>(GetOwner()->GetOwner()), this);
		}
		else
		{
		FPointDamageEvent DamageEvent(Damage, FHitResult(), FVector::ZeroVector, nullptr);
		HitActor->TakeDamage(Damage, DamageEvent, Cast<AController>(GetOwner()->GetOwner()), this);}
	}
}

void AWeapon::ResetFire()
{
	bCanFire = true;
}
// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

