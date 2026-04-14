// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleTestActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
AModuleTestActor::AModuleTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMesh.Object);
	}
}

// Called when the game starts or when spawned
void AModuleTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModuleTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

