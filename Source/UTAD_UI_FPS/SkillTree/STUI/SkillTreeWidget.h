// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeWidget.generated.h"

class UHorizontalBox;
struct FTreeBranch;
class USkillTreeBranchWidget;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTreeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	void AddBranch(const FTreeBranch& _inBranch);

	void UpdateVerticalIndex(int _modification);
	void UpdateHorizontalIndex(int _modification);
	
	UPROPERTY(EditAnywhere, Category = "SkillTree") 
	TSubclassOf<USkillTreeBranchWidget> SkillTreeBranchWidgetType;

	int verticalIndex;
	int horizontalIndex;
	
private:
	UPROPERTY()
	TArray<USkillTreeBranchWidget*> BranchWidgets;
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* BranchBox;
};
