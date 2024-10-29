// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeObjectWidget.h"

#include "Components/TextBlock.h"
#include "UTAD_UI_FPS/SkillTree/SkillTree.h"

void USkillTreeObjectWidget::InitializeSkill(const FTreeSkill& _inSkill)
{
	SkillNameText->SetText(_inSkill.SkillName);
	SkillDescriptionText->SetText(_inSkill.SkillDescription);
	FString skillCostString = FString::FromInt(_inSkill.SkillCost);
	SkillCostText->SetText(FText::FromString(skillCostString)); 
}
