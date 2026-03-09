// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorTestClass.h"

// Sets default values
AMyActorTestClass::AMyActorTestClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActorTestClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorTestClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AMyActorTestClass::GetTargetActorLocation() const
{
    if (TargetActor)
    {
        return TargetActor->GetActorLocation();
    }
    return FVector::ZeroVector;
}

