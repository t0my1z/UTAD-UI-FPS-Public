// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillTree.h"
#include "Components/ActorComponent.h"
#include "SkillTreeComponent.generated.h"

class USkillTreeWidget;
class AUTAD_UI_FPSCharacter;
class UDataTable;
class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnlockState);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTAD_UI_FPS_API USkillTreeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USkillTreeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void LoadSkillTree(FName RowName);

	void CreateSkillTreeUI();

#pragma region Input Functions
	
	void SetupInput();

	UFUNCTION()
	void ShowSkillTree();

	UFUNCTION()
	void AddSkillPoints();

	UFUNCTION()
	void StartUnlockingSkill();
	
	UFUNCTION()
	void CompleteUnlockingSkill();
	
	UFUNCTION()
	void StopUnlockingSkill();

	UFUNCTION()
	void NavigateTree(const FInputActionValue& Value);

#pragma endregion 
	
private:

	int GetCurrentSelectedSkillCost();
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Tree")
	FName DTRowNameToInit;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Tree")
	UDataTable* SkillTreeDT;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Tree")
	TSubclassOf<USkillTreeWidget> SkillTreeWidgetType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Tree")
	int NumOfSkillPointsToAdd; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Tree")
	bool DebugOn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* SkillTreeMappingContext; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ToggleSTAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* AddSTPointsAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* UnlockSTSkillAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* NavigateSTAction; 

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnUnlockState OnUnlockStart;
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnUnlockState OnUnlockComplete;
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnUnlockState OnUnlockEnd;
	
	float TimeToUnlockSkill;
	float UnlockSkillTimer; 
	
private:
	UPROPERTY() 
	FSkillTree CurrentSkillTree;

	UPROPERTY() 
	AUTAD_UI_FPSCharacter* Character;

	UPROPERTY()
	USkillTreeWidget* SkillTreeWidget;

	bool skillTreeInScreen;
	
	bool unlockingSkill;
};
