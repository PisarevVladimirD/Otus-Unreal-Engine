// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "ModularWeaponSystem.h"
#include "ModularWeaponActor.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void CallPluginFunctionAdd();
	void CallPluginFunctionRemove();
private:
	AModularWeaponActor* PluginInstance; 

	void CallAddFunctionPlugin(); 
	void CallRemoveFunctionPlugin();
	void SpawnModuleTestActor();
	void SpawnPluginTestActor();
	
	FVector GetSpawnLocationInFrontOfCharacter(float Distance = 300.0f) const;

};

