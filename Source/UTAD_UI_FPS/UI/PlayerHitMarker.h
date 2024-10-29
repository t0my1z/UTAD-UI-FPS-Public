// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHitMarker.generated.h"

class AUTAD_UI_FPSCharacter;
class UImage;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerHitMarker : public UUserWidget
{
	GENERATED_BODY()

	
public:

	virtual void NativeDestruct() override;
	
	void Setup(AUTAD_UI_FPSCharacter* _inCharacter);

private:
	
	UFUNCTION()
	void DamageTaken(float _HealthPercentage);

public:
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
	TMap<float, FLinearColor> DamagePercentImageColorMap;
	
private:
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* DamageAnimation;  
	
	UPROPERTY(meta = (BindWidget))
	UImage* DamageImage;

	UPROPERTY()
	AUTAD_UI_FPSCharacter* Character; 
};
