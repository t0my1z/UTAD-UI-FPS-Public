// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.generated.h"

class UImage;
class UTP_WeaponComponent;
class AUTAD_UI_FPSCharacter;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UCrosshair : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();
	
	UFUNCTION(BlueprintCallable)
	void Setup(AUTAD_UI_FPSCharacter* _inCharacter);

	void SetupWeaponCmp(UTP_WeaponComponent* _inWeaponCmp);
	
	UFUNCTION()
	void PlayShootAnimation();
	
	UPROPERTY(EditAnywhere, Category = "Crosshair")
	FLinearColor EnemySightedColor;

private:
	UFUNCTION()
	void EnemyDetected(bool _inState);
private:

	UPROPERTY(meta = (BindWidget))
	UImage* CrosshairImg;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShootAnimation; 
	
	FLinearColor OriginalColor;

	UPROPERTY()
	AUTAD_UI_FPSCharacter* Character;

	UPROPERTY()
	UTP_WeaponComponent* WeaponCmp;
	
	bool PlayerShooting;
	
};
