// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadBar.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "../TP_WeaponComponent.h"
#include "Components/ProgressBar.h"


void UReloadBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(isReloading)
	{
		float NormalizedValue = FMath::GetMappedRangeValueClamped(FVector2D(0, WeaponCmp->ReloadTime), FVector2D(0.0f, 1.0f), WeaponCmp->ReloadTimer);
		UpdateReloadBarValue(NormalizedValue); 
	}
}

void UReloadBar::NativeDestruct()
{
	Super::NativeDestruct();

	if(WeaponCmp)
	{
		WeaponCmp->OnReloadStart.RemoveDynamic(this, &UReloadBar::OnReloadStart);
		WeaponCmp->OnReloadEnd.RemoveDynamic(this, &UReloadBar::OnReloadEnd);
	}
}

void UReloadBar::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UReloadBar::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UReloadBar::SetupWeaponCmp(UTP_WeaponComponent* _inWeaponCmp)
{
	if(_inWeaponCmp)
	{
		WeaponCmp = _inWeaponCmp;
		WeaponCmp->OnReloadStart.AddDynamic(this, &UReloadBar::OnReloadStart);
		WeaponCmp->OnReloadEnd.AddDynamic(this, &UReloadBar::OnReloadEnd);
	}
}

void UReloadBar::OnReloadStart()
{
	isReloading = true;
}

void UReloadBar::OnReloadEnd()
{
	isReloading = false;
	ReloadBar->SetPercent(0);
}

void UReloadBar::UpdateReloadBarValue(float NewValue)
{
	if(ReloadBar)
	{
		ReloadBar->SetPercent(NewValue); 
	}
}
