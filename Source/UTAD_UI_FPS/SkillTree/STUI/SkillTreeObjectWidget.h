// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeObjectWidget.generated.h"

class UTextBlock;
struct FTreeSkill;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTreeObjectWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeSkill(const FTreeSkill& _inSkill); 

private:

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SkillNameText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SkillDescriptionText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SkillCostText;
};
