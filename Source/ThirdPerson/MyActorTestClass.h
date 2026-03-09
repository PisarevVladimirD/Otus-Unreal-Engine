// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorTestClass.generated.h"

UCLASS()
class THIRDPERSON_API AMyActorTestClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorTestClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	AActor* TargetActor;
	UFUNCTION(BlueprintCallable, Category = "Test")
	FVector GetTargetActorLocation() const;
};
