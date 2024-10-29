// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHealthBar.generated.h"

class AUTAD_UI_FPSCharacter;
class UProgressBar;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIHealthPercentageChanged, int, HealthPercentage);

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual bool Initialize() override;

	virtual void NativeDestruct() override;
	
	void Setup(AUTAD_UI_FPSCharacter* _inCharacter);
	
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnUIHealthPercentageChanged OnHealthPercentageChanged;

	UPROPERTY(EditAnywhere, Category = "Health Bar")
	FLinearColor LowHealthBlinkColor;
	UPROPERTY(EditAnywhere, Category = "Health Bar")
	float TimeToChangeColor = 1.f;
	
protected:

	// Bind to a UProgressBar in the Blueprint
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:

	UPROPERTY()
	AUTAD_UI_FPSCharacter* Character;
	
	FLinearColor OriginalBarColor;
	
	float BlinkTimer = 0.f;
	bool bIsLowHealth = false;
	bool bBlinkTurningRed = true;

	UFUNCTION()
	void UpdatePlayerHealthBar(int NewHealth, int MaxHealth);

	void LowHealthBlink(float _deltaTime);
};
