// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"

void UInventoryWidget::InitializeWidget(UInventoryComponent* InInventory)
{
	if (!InInventory) return;
	
	if (BoundInventory)
	{
		BoundInventory->OnInventoryChanged.RemoveDynamic(this, &UInventoryWidget::OnInventoryUpdated);
	}

	BoundInventory = InInventory;
	BoundInventory->OnInventoryChanged.AddDynamic(this, &UInventoryWidget::OnInventoryUpdated);
	RefreshDisplay();
}

void UInventoryWidget::OnInventoryUpdated()
{
	RefreshDisplay();
}

void UInventoryWidget::RefreshDisplay()
{
	if (!BoundInventory || !AmmoText || !WeaponsContainer) return;
	
	AmmoText->SetText(FText::AsNumber(BoundInventory->GetUniversalAmmo()));
	
	WeaponsContainer->ClearChildren();
	
	for (EWeaponType Weapon : BoundInventory->GetOwnedWeapons())
	{
		if (WeaponIconWidgetClass)
		{
			UUserWidget* IconWidget = CreateWidget<UUserWidget>(GetWorld(), WeaponIconWidgetClass);
			if (IconWidget)
			{
				UImage* WeaponImage = Cast<UImage>(IconWidget->GetWidgetFromName(TEXT("WeaponIcon")));
				if (WeaponImage && WeaponIcons.Contains(Weapon))
				{
					WeaponImage->SetBrushFromTexture(WeaponIcons[Weapon]);
				}
				WeaponsContainer->AddChild(IconWidget);
			}
		}
	}
}
