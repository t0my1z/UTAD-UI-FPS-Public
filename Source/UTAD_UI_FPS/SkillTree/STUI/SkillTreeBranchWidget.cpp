// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBranchWidget.h"

#include "SkillTreeObjectWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "UTAD_UI_FPS/SkillTree/SkillTree.h"

void USkillTreeBranchWidget::InitializeBranch(const FTreeBranch& _inBranchData, USkillTreeComponent* _inSTCmp)
{
	BranchNameText->SetText(_inBranchData.BranchName);

	for (const FTreeSkill& TreeSkill : _inBranchData.SkillsInBranch)
	{
		AddSkillObject(TreeSkill, _inSTCmp);  
	}
}

void USkillTreeBranchWidget::AddSkillObject(const FTreeSkill& _inSkill, USkillTreeComponent* _inSTCmp)
{
	if (!SkillTreeObjectWidgetType || !SkillBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillTreeObjectWidgetType or SkillBox is not set in SkillTreeWidget"));
		return;
	}
	
	USkillTreeObjectWidget* NewSkillWidget = CreateWidget<USkillTreeObjectWidget>(GetWorld(), SkillTreeObjectWidgetType);
	if (NewSkillWidget)
	{
		NewSkillWidget->InitializeSkill(_inSkill, _inSTCmp);
		
		UVerticalBoxSlot* boxSlot = SkillBox->AddChildToVerticalBox(NewSkillWidget); 
		if(boxSlot) boxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));  
		SkillWidgets.Add(NewSkillWidget);
	}
}
