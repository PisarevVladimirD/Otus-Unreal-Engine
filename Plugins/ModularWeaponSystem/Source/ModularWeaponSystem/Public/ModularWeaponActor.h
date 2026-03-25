// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "ModularWeaponActor.generated.h"


UCLASS()
class MODULARWEAPONSYSTEM_API AModularWeaponActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AModularWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag ShotSocket;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, FName> Sockets;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void AddModule(TSubclassOf<UWeaponComponent> ModuleClass);

	UFUNCTION(BlueprintCallable)
	void RemoveModule(const FGameplayTag Module);

	UFUNCTION(BlueprintCallable)
	float GetSummaryDamage() const;

	UFUNCTION(BlueprintCallable)
	void Shot(FVector ShotLocation);
	void AddModule();
	void RemoveModule();

private:

	UPROPERTY()
	TMap<FGameplayTag, UWeaponComponent*> Modules;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float BaseDamage = 5.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
};
