// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeWidget.h"

#include "SkillTreeBranchWidget.h"
#include "SkillTreeObjectWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"
#include "UTAD_UI_FPS/SkillTree/SkillTreeComponent.h"

void USkillTreeWidget::InitVars(USkillTreeComponent* _inSTCmp)
{
	if(_inSTCmp)
	{
		SkillTreeCmp = _inSTCmp;
	}
}

void USkillTreeWidget::Setup()
{
	if(SkillTreeCmp)
	{
		AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(SkillTreeCmp->GetOwner());
		
		if(Character)
		{
			UpdateSkillPoints(Character->SkillPoints);
			Character->OnSkillPointChanged.AddDynamic(this, &USkillTreeWidget::UpdateSkillPoints);
		}
		
		verticalIndex = 0;
		//New Branch Gains Focus
		if(BranchWidgets.IsEmpty()) return;
		BranchWidgets[horizontalIndex]->FocusGained();
		BranchWidgets[horizontalIndex]->GetSkillObjectWidgets()[verticalIndex]->Focused();
	}
}

void USkillTreeWidget::CloseUp()
{
	if(SkillTreeCmp)
	{
		AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(SkillTreeCmp->GetOwner());
		if(Character) Character->OnSkillPointChanged.RemoveDynamic(this, &USkillTreeWidget::UpdateSkillPoints);
		
		BranchWidgets[horizontalIndex]->FocusLost();
		BranchWidgets[horizontalIndex]->GetSkillObjectWidgets()[verticalIndex]->Unfocused();
	}
}

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
		NewBranchWidget->InitializeBranch(_inBranch, SkillTreeCmp);
		
		// Add the new widget to the VerticalBox
		UHorizontalBoxSlot* boxSlot = BranchBox->AddChildToHorizontalBox(NewBranchWidget);
		if(boxSlot) boxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); 
		// Add the widget to the BranchWidgets array for tracking
		BranchWidgets.Add(NewBranchWidget);
	}
}

void USkillTreeWidget::UpdateVerticalIndex(int _modification)
{
	int NewVertical = verticalIndex + _modification;
	
	if(NewVertical < 0) NewVertical = BranchWidgets[horizontalIndex]->NumOfSkillsInBranch();
	if(NewVertical > BranchWidgets[horizontalIndex]->NumOfSkillsInBranch()) NewVertical = 0;
	
	BranchWidgets[horizontalIndex]->GetSkillObjectWidgets()[verticalIndex]->Unfocused();
	
	verticalIndex = NewVertical;
	
	BranchWidgets[horizontalIndex]->GetSkillObjectWidgets()[verticalIndex]->Focused();
}

void USkillTreeWidget::UpdateHorizontalIndex(int _modification)
{
	int NewHorizontal = horizontalIndex + _modification;

	if(NewHorizontal < 0) NewHorizontal = BranchWidgets.Num() -1;
	if(NewHorizontal > BranchWidgets.Num() -1) NewHorizontal = 0;

	//Old Branch Loses Focus
	BranchWidgets[horizontalIndex]->FocusLost();
	BranchWidgets[horizontalIndex]->GetSkillObjectWidgets()[verticalIndex]->Unfocused();
	
	//Update Index
	horizontalIndex = NewHorizontal;
	
	//New Branch Gains Focus
	BranchWidgets[horizontalIndex]->FocusGained();
	BranchWidgets[horizontalIndex]->GetSkillObjectWidgets()[verticalIndex]->Focused();
}

void USkillTreeWidget::UpdateSkillPoints(int _inPoints)
{
	if(SkillPointText)
	{ 
		FString ammoMsg = FString::FromInt(_inPoints);
		SkillPointText->SetText(FText::FromString(ammoMsg));
	}
}
