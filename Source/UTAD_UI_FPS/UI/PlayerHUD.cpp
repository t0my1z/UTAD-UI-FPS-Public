// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Crosshair.h"
#include "AmmoCounter.h"
#include "PlayerHealthBar.h"
#include "PlayerHitMarker.h"
#include "ReloadBar.h"

void UPlayerHUD::ShowNoWeapon()
{
	PlayerHealthBar->Show();
	Minimap->SetVisibility(ESlateVisibility::HitTestInvisible);
	ReloadBar->Hide();
	Crosshair->Hide();
	AmmoCounter->Hide(); 
}

void UPlayerHUD::ShowAll()
{
	PlayerHealthBar->Show();
	ReloadBar->Show();
	Crosshair->Show();
	AmmoCounter->Show();
	Minimap->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UPlayerHUD::Hide()
{
	PlayerHealthBar->Hide();
	ReloadBar->Hide();
	Crosshair->Hide();
	AmmoCounter->Hide();
	Minimap->SetVisibility(ESlateVisibility::Collapsed);
}

void UPlayerHUD::Setup(AUTAD_UI_FPSCharacter* _inCharacter)
{
	PlayerHealthBar->Setup(_inCharacter);
	Crosshair->Setup(_inCharacter);
	AmmoCounter->Setup(_inCharacter);
	PlayerHitMarker->Setup(_inCharacter); 
}
