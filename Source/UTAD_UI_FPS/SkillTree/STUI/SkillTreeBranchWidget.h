// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeBranchWidget.generated.h"

class USkillTreeComponent;
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

	UFUNCTION(BlueprintImplementableEvent, Category="Custom")
	void FocusGained();

	UFUNCTION(BlueprintImplementableEvent, Category="Custom")
	void FocusLost();
	
	void InitializeBranch(const FTreeBranch& _inBranchData, USkillTreeComponent* _inSTCmp);

	int NumOfSkillsInBranch() const { return SkillWidgets.Num() - 1;}
	
	UPROPERTY(EditAnywhere, Category = "SkillTree")  
	TSubclassOf<USkillTreeObjectWidget> SkillTreeObjectWidgetType;
	
	TArray<USkillTreeObjectWidget*>& GetSkillObjectWidgets() { return SkillWidgets; }

	UFUNCTION(BlueprintCallable)
	UTextBlock* GetBranchNameText() { return BranchNameText; }
	
private:
	void AddSkillObject(const FTreeSkill& _inSkill, USkillTreeComponent* _inSTCmp);
	
private:
	UPROPERTY()
	TArray<USkillTreeObjectWidget*> SkillWidgets;  

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BranchNameText;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* SkillBox;  
};
