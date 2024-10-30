// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeObjectWidget.generated.h"

class USkillTreeComponent;
class UProgressBar;
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

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintImplementableEvent, Category="Custom")
	void FocusGained();

	UFUNCTION(BlueprintImplementableEvent, Category="Custom")
	void FocusLost();
	
	void InitializeSkill(const FTreeSkill& _inSkill, USkillTreeComponent* _inSTCmp); 

	void Focused();

	void Unfocused();
	
	UFUNCTION(BlueprintCallable)
	void BindUnlockFuncs();

	UFUNCTION(BlueprintCallable)
	void UnbindUnlockFuncs();
	
private:

	void UpdateUnlockProgressBar(float _updatedValue);

	UFUNCTION()
	void UnlockStart();
	UFUNCTION()
	void UnlockComplete();
	UFUNCTION()
	void UnlockEnd();
	
private:
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SkillNameText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SkillDescriptionText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SkillCostText;
	UPROPERTY(meta =(BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY() 
	USkillTreeComponent* SkillTreeCmp;
	
	bool isGettingUnlocked = false;
	bool isUnlocked = false;
};
