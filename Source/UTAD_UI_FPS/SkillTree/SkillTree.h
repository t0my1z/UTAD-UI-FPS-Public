#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillTree.generated.h" 

USTRUCT(Blueprintable)
struct FTreeSkill 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int SkillCost;
};

USTRUCT(Blueprintable)
struct FTreeBranch
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText BranchName; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTreeSkill> SkillsInBranch; 
};

USTRUCT(BlueprintType)
struct FSkillTree : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTreeBranch> SkillBranches;
};