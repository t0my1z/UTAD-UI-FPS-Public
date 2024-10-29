// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SplashArtScreen.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USplashArtScreen : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

	void Hide();
	
private:
	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundImage;

	FTimerHandle TimerHandle;
};
