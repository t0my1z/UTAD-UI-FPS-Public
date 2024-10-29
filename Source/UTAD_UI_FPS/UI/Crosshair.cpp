// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"

#include "Components/Image.h"
#include "UTAD_UI_FPS/TP_WeaponComponent.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

bool UCrosshair::Initialize()
{
	bool init = Super::Initialize();

	//Set OrigColor
	if(CrosshairImg)
	{
		OriginalColor = CrosshairImg->GetColorAndOpacity();
	}
	
	return init;
}

void UCrosshair::NativeDestruct()
{
	Super::NativeDestruct();

	if(WeaponCmp)
	{
		WeaponCmp->OnEnemyTargeted.RemoveDynamic(this, &UCrosshair::EnemyDetected);
		WeaponCmp->OnWeaponShot.RemoveDynamic(this, &UCrosshair::PlayShootAnimation); 
	}
}

void UCrosshair::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCrosshair::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UCrosshair::Setup(AUTAD_UI_FPSCharacter* _inCharacter)
{
	if(_inCharacter)
	{
		Character = _inCharacter;
	}
}

void UCrosshair::SetupWeaponCmp(UTP_WeaponComponent* _inWeaponCmp)
{
	if(_inWeaponCmp)
	{
		WeaponCmp = _inWeaponCmp;
		WeaponCmp->OnEnemyTargeted.AddDynamic(this, &UCrosshair::EnemyDetected);
		WeaponCmp->OnWeaponShot.AddDynamic(this, & UCrosshair::PlayShootAnimation);
	}
}

void UCrosshair::PlayShootAnimation()
{
	if(ShootAnimation)
	{
		if(IsPlayingAnimation())
		{
			StopAnimation(ShootAnimation);
		}

		PlayAnimation(ShootAnimation);
	}
}

void UCrosshair::EnemyDetected(bool _inState)
{
	if(_inState)
	{
		CrosshairImg->SetColorAndOpacity(EnemySightedColor);
	}
	else
	{
		CrosshairImg->SetColorAndOpacity(OriginalColor);
	}
}
