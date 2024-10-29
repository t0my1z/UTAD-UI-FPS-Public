// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCounter.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "../TP_WeaponComponent.h"
#include "Components/TextBlock.h"

void UAmmoCounter::NativeDestruct()
{
	Super::NativeDestruct();

	if(Character)
	{
		Character->OnTotalBulletsChanged.RemoveDynamic(this, &UAmmoCounter::UpdateTotalAmmo); 
	}
	
	if(WeaponCmp)
	{
		WeaponCmp->OnWeaponReload.RemoveDynamic(this, &UAmmoCounter::UpdateCurrentAmmo); 
	}
}

void UAmmoCounter::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UAmmoCounter::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UAmmoCounter::Setup(AUTAD_UI_FPSCharacter* _inCharacter)
{
	if(_inCharacter)
	{
		Character = _inCharacter;
		Character->OnTotalBulletsChanged.AddDynamic(this, &UAmmoCounter::UpdateTotalAmmo);
	}
}

void UAmmoCounter::SetupWeaponCmp(UTP_WeaponComponent* _inWeaponCmp)
{
	if(_inWeaponCmp)
	{
		WeaponCmp = _inWeaponCmp;
		WeaponCmp->OnWeaponReload.AddDynamic(this, &UAmmoCounter::UpdateCurrentAmmo);	
	}
}

void UAmmoCounter::UpdateCurrentAmmo(int NewCurrentAmmo)
{
	if(CurrentAmmo)
	{
		FString ammoMsg = FString::FromInt(NewCurrentAmmo);
		CurrentAmmo->SetText(FText::FromString(ammoMsg));
	}
}

void UAmmoCounter::UpdateTotalAmmo(int NewTotalAmmo)
{
	if(TotalAmmo)
	{
		FString ammoMsg = FString::FromInt(NewTotalAmmo);
		TotalAmmo->SetText(FText::FromString(ammoMsg));
	}
}
