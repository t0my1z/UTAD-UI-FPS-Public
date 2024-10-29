// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UPlayerHitMarker;
class UAmmoCounter;
class UCrosshair;
class UPlayerHealthBar;
class UReloadBar;
class AUTAD_UI_FPSCharacter;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	/** Show the Minimap and the PlayerHealthBar */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void ShowNoWeapon();
	
	/** Show all the widgets */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void ShowAll();

	/** Hide all the widgets */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	UFUNCTION()
	void Setup(AUTAD_UI_FPSCharacter* _inCharacter);

	UFUNCTION(BlueprintCallable) 
	UCrosshair* GetCrosshairUI() { return Crosshair; }

	UFUNCTION(BlueprintCallable) 
	UAmmoCounter* GetAmmoCounterUI() { return AmmoCounter; }
	
	UFUNCTION(BlueprintCallable) 
	UReloadBar* GetReloadBarUI() { return ReloadBar; }
	
protected:

	UPROPERTY(meta = (BindWidget))
	UPlayerHealthBar* PlayerHealthBar;
	UPROPERTY(meta = (BindWidget))
	UReloadBar* ReloadBar;
	UPROPERTY(meta = (BindWidget))
	UCrosshair* Crosshair; 
	UPROPERTY(meta = (BindWidget))
	UAmmoCounter* AmmoCounter;
	UPROPERTY(meta = (BindWidget))
	UUserWidget* Minimap;
	UPROPERTY(meta = (BindWidget))
	UPlayerHitMarker* PlayerHitMarker;
};
