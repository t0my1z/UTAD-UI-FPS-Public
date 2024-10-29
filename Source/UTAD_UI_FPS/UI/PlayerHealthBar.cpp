// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthBar.h"
#include "Components/ProgressBar.h"
#include "Math/Color.h"
#include "Styling/SlateColor.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

#define BLINK_ANIMATION_TIME 1.f
#define BLINK_THRESHOLD 0.25f

void UPlayerHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	LowHealthBlink(InDeltaTime);
}

bool UPlayerHealthBar::Initialize()
{
	bool init = Super::Initialize();

	//Set OrigColor
	if(HealthBar)
	{
		OriginalBarColor = HealthBar->GetFillColorAndOpacity();
	}
	
	return init;
}

void UPlayerHealthBar::NativeDestruct()
{
	Super::NativeDestruct();

	if(Character)
	{
		Character->HealthChanged.RemoveDynamic(this, &UPlayerHealthBar::UpdatePlayerHealthBar);
	}
}

void UPlayerHealthBar::Setup(AUTAD_UI_FPSCharacter* _inCharacter)
{
	if(_inCharacter)
	{
		Character = _inCharacter; 
		Character->HealthChanged.AddDynamic(this, &UPlayerHealthBar::UpdatePlayerHealthBar);
	}
}

void UPlayerHealthBar::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UPlayerHealthBar::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UPlayerHealthBar::UpdatePlayerHealthBar(int NewHealth, int MaxHealth)
{
	// Prevent division by zero
	if (MaxHealth <= 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxHealth is zero or less, cannot calculate health percentage."));
		return;
	}

	// Calculate health percentage as a float between 0.0 and 1.0
	float HealthPercentage = static_cast<float>(NewHealth) / static_cast<float>(MaxHealth);

	//If health is lower than 25%, start blinking. Else, reset to original color
	if(HealthPercentage <= 0.25f)
	{
		bIsLowHealth = true;
		bBlinkTurningRed = true;
	}
	else if(bIsLowHealth)
	{
		bIsLowHealth = false;
		BlinkTimer = 0;
		HealthBar->SetFillColorAndOpacity(OriginalBarColor);
	}
	
	HealthBar->SetPercent(HealthPercentage);
	
	if(OnHealthPercentageChanged.IsBound()) OnHealthPercentageChanged.Broadcast(HealthPercentage);
}

void UPlayerHealthBar::LowHealthBlink(float _deltaTime)
{
	if(bIsLowHealth)
	{
		BlinkTimer += _deltaTime;

		// Calculate blend factor based on time elapsed
		float BlendFactor = FMath::Sin((BlinkTimer / TimeToChangeColor) * PI) * 0.5f + 0.5f; // Oscillates smoothly between 0 and 1
		FLinearColor CurrentColor = FMath::Lerp(OriginalBarColor, LowHealthBlinkColor, BlendFactor);
		HealthBar->SetFillColorAndOpacity(CurrentColor);

		if(BlinkTimer >= TimeToChangeColor) BlinkTimer = 0.f;
	}
}
