// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHitMarker.h"

#include "Components/Image.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void UPlayerHitMarker::NativeDestruct()
{
	Super::NativeDestruct();

	if(Character)
	{
		Character->OnDamaged.RemoveDynamic(this, &UPlayerHitMarker::DamageTaken);
	}
}

void UPlayerHitMarker::Setup(AUTAD_UI_FPSCharacter* _inCharacter)
{
	if(_inCharacter)
	{
		Character = _inCharacter; 
		Character->OnDamaged.AddDynamic(this, &UPlayerHitMarker::DamageTaken);
	}
}

void UPlayerHitMarker::DamageTaken(float _HealthPercentage)
{
	for (TTuple<float, FLinearColor>& Element : DamagePercentImageColorMap)
	{
		if(_HealthPercentage >= Element.Key)
		{
			DamageImage->SetColorAndOpacity(Element.Value);
			break;
		}
	}
	
	if(IsAnimationPlaying(DamageAnimation)) StopAnimation(DamageAnimation);

	PlayAnimation(DamageAnimation);
}
