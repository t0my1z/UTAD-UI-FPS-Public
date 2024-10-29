// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeWidget.h"

#include "SkillTreeBranchWidget.h"
#include "Components/HorizontalBox.h"
#include "UTAD_UI_FPS/SkillTree/SkillTree.h"

void USkillTreeWidget::AddBranch(const FTreeBranch& _inBranch)
{
	if (!SkillTreeBranchWidgetType || !BranchBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillTreeBranchWidgetType or BranchBox is not set in SkillTreeWidget"));
		return;
	}
	
	// Create an instance of the SkillTreeBranchWidgetType
	USkillTreeBranchWidget* NewBranchWidget = CreateWidget<USkillTreeBranchWidget>(GetWorld(), SkillTreeBranchWidgetType);
	if (NewBranchWidget)
	{
		// Optionally, initialize NewBranchWidget with _inBranch data here
		NewBranchWidget->InitializeBranch(_inBranch);
		
		// Add the new widget to the VerticalBox
		BranchBox->AddChildToHorizontalBox(NewBranchWidget);
		
		// Add the widget to the BranchWidgets array for tracking
		BranchWidgets.Add(NewBranchWidget);
	}
}

void USkillTreeWidget::UpdateVerticalIndex(int _modification)
{
	int NewVertical = verticalIndex + _modification;

	if(NewVertical < 0) NewVertical = BranchWidgets[horizontalIndex]->NumOfSkillsInBranch();
	if(NewVertical > BranchWidgets[horizontalIndex]->NumOfSkillsInBranch()) NewVertical = 0;

	verticalIndex = NewVertical;
}

void USkillTreeWidget::UpdateHorizontalIndex(int _modification)
{
	int NewHorizontal = horizontalIndex + _modification;

	if(NewHorizontal < 0) NewHorizontal = BranchWidgets.Num() -1;
	if(NewHorizontal > BranchWidgets.Num() -1) NewHorizontal = 0;

	horizontalIndex = NewHorizontal;
}
