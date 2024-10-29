// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoCounter.generated.h"

class UTextBlock;
class UTP_WeaponComponent;
class AUTAD_UI_FPSCharacter;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UAmmoCounter : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	UFUNCTION(BlueprintCallable)
	void Setup(AUTAD_UI_FPSCharacter* _inCharacter);

	void SetupWeaponCmp(UTP_WeaponComponent* _inWeaponCmp);
	
private:

	UFUNCTION()
	void UpdateCurrentAmmo(int NewCurrentAmmo);
	UFUNCTION() 
	void UpdateTotalAmmo(int NewTotalAmmo);

private:
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentAmmo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalAmmo; 
	
	UPROPERTY() 
	AUTAD_UI_FPSCharacter* Character;

	UPROPERTY() 
	UTP_WeaponComponent* WeaponCmp;
};
