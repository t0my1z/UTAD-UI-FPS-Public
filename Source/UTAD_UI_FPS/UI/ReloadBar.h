// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReloadBar.generated.h"

class UProgressBar;
class UTP_WeaponComponent;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UReloadBar : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	void SetupWeaponCmp(UTP_WeaponComponent* _inWeaponCmp);

	UFUNCTION()
	void OnReloadStart();
	UFUNCTION()
	void OnReloadEnd();
	
private:

	void UpdateReloadBarValue(float NewValue);

private:
	UPROPERTY()
	UTP_WeaponComponent* WeaponCmp;
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ReloadBar; 
	
	bool isReloading = false; 
};
