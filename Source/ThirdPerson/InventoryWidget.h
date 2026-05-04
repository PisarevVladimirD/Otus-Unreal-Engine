// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item_Pickup_System/WeaponType.h"
#include "InventoryWidget.generated.h"

class UInventoryComponent;
class UTextBlock;
class UWrapBox;   
class UImage;

UCLASS()
class THIRDPERSON_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Inventory UI")
	void InitializeWidget(UInventoryComponent* InInventory);

protected:
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AmmoText;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* WeaponsContainer;   

	UPROPERTY(EditDefaultsOnly, Category = "Inventory UI")
	TMap<EWeaponType, UTexture2D*> WeaponIcons;   
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory UI")
	TSubclassOf<UUserWidget> WeaponIconWidgetClass;

	UPROPERTY()
	UInventoryComponent* BoundInventory;

	UFUNCTION()
	void OnInventoryUpdated();

	void RefreshDisplay();

};
