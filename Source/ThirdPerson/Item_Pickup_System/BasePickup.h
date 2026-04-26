// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemTypes.h"
#include "GameFramework/Actor.h"
#include "Item_Pickup_System/PickupInterface.h"
#include "BasePickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS(Abstract, Blueprintable)
class ABasePickup : public AActor, public IPickupInterface
{
	GENERATED_BODY()

public:
	ABasePickup();

	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
	virtual void PickUp_Implementation(AActor* Picker) override;

	
	virtual EItemType GetItemType() const PURE_VIRTUAL(ABasePickup::GetItemType, return EItemType::None;);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;
};
