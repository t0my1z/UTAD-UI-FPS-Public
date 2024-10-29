// Fill out your copyright notice in the Description page of Project Settings.


#include "SplashArtScreen.h"

void USplashArtScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USplashArtScreen::Hide, 4.f, false);
	}
}

void USplashArtScreen::Hide()
{
	RemoveFromParent(); 
}
