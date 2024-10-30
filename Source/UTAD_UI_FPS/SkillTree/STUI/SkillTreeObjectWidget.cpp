// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeObjectWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UTAD_UI_FPS/SkillTree/SkillTree.h"
#include "UTAD_UI_FPS/SkillTree/SkillTreeComponent.h"

void USkillTreeObjectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(isGettingUnlocked && !isUnlocked) 
	{ 
		float NormalizedValue = FMath::GetMappedRangeValueClamped(FVector2D(0, SkillTreeCmp->TimeToUnlockSkill), FVector2D(0.0f, 1.0f), SkillTreeCmp->UnlockSkillTimer);
		UpdateUnlockProgressBar(NormalizedValue); 
	}
}

void USkillTreeObjectWidget::InitializeSkill(const FTreeSkill& _inSkill, USkillTreeComponent* _inSTCmp)
{
	SkillNameText->SetText(_inSkill.SkillName);
	SkillDescriptionText->SetText(_inSkill.SkillDescription);
	FString skillCostString = FString::FromInt(_inSkill.SkillCost);
	SkillCostText->SetText(FText::FromString(skillCostString));

	if(_inSTCmp)
	{
		SkillTreeCmp = _inSTCmp;
	}
}

void USkillTreeObjectWidget::Focused()
{
	BindUnlockFuncs();
	FocusGained();
}

void USkillTreeObjectWidget::Unfocused()
{
	UnbindUnlockFuncs();
	FocusLost();
}

void USkillTreeObjectWidget::BindUnlockFuncs()
{
	if(SkillTreeCmp)
	{
		SkillTreeCmp->OnUnlockStart.AddDynamic(this, &USkillTreeObjectWidget::UnlockStart);
		SkillTreeCmp->OnUnlockComplete.AddDynamic(this, &USkillTreeObjectWidget::UnlockComplete);
		SkillTreeCmp->OnUnlockEnd.AddDynamic(this, &USkillTreeObjectWidget::UnlockEnd);
	}
}

void USkillTreeObjectWidget::UnbindUnlockFuncs()
{
	if(SkillTreeCmp)
	{
		SkillTreeCmp->OnUnlockStart.RemoveDynamic(this, &USkillTreeObjectWidget::UnlockStart);
		SkillTreeCmp->OnUnlockComplete.RemoveDynamic(this, &USkillTreeObjectWidget::UnlockComplete);
		SkillTreeCmp->OnUnlockEnd.RemoveDynamic(this, &USkillTreeObjectWidget::UnlockEnd);
	}
}

void USkillTreeObjectWidget::UpdateUnlockProgressBar(float _updatedValue)
{
	if(ProgressBar)
	{
		ProgressBar->SetPercent(_updatedValue); 
	}
}

void USkillTreeObjectWidget::UnlockStart()
{
	if(isUnlocked) return;

	isGettingUnlocked = true;
}

void USkillTreeObjectWidget::UnlockComplete()
{
	if(isUnlocked) return;
	
	isUnlocked = true;
	isGettingUnlocked = false;
}

void USkillTreeObjectWidget::UnlockEnd()
{
	if(isUnlocked) return;
	
	isGettingUnlocked = false;
	if(ProgressBar)
	{
		ProgressBar->SetPercent(0); 
	}
}
