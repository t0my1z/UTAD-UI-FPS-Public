// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBranchWidget.h"

#include "SkillTreeObjectWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "UTAD_UI_FPS/SkillTree/SkillTree.h"

void USkillTreeBranchWidget::InitializeBranch(const FTreeBranch& _inBranchData)
{
	BranchNameText->SetText(_inBranchData.BranchName);

	for (const FTreeSkill& TreeSkill : _inBranchData.SkillsInBranch)
	{
		AddSkillObject(TreeSkill); 
	}
}

void USkillTreeBranchWidget::AddSkillObject(const FTreeSkill& _inSkill)
{
	if (!SkillTreeObjectWidgetType || !SkillBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillTreeObjectWidgetType or SkillBox is not set in SkillTreeWidget"));
		return;
	}
	
	USkillTreeObjectWidget* NewSkillWidget = CreateWidget<USkillTreeObjectWidget>(GetWorld(), SkillTreeObjectWidgetType);
	if (NewSkillWidget)
	{
		NewSkillWidget->InitializeSkill(_inSkill);
		
		SkillBox->AddChildToVerticalBox(NewSkillWidget); 
		
		SkillWidgets.Add(NewSkillWidget);
	}
}
