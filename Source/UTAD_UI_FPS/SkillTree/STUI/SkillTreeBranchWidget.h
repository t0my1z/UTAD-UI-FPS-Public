// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeBranchWidget.generated.h"

class UVerticalBox;
struct FTreeBranch;
class UTextBlock;
struct FTreeSkill;
class USkillTreeObjectWidget;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTreeBranchWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeBranch(const FTreeBranch& _inBranchData);

	int NumOfSkillsInBranch() const { return SkillWidgets.Num() - 1;}
	
	UPROPERTY(EditAnywhere, Category = "SkillTree")  
	TSubclassOf<USkillTreeObjectWidget> SkillTreeObjectWidgetType;

private:
	void AddSkillObject(const FTreeSkill& _inSkill);
	
private:
	UPROPERTY()
	TArray<USkillTreeObjectWidget*> SkillWidgets;  

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BranchNameText;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* SkillBox;  
};
