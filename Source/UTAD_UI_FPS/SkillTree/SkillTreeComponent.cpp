// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "STUI/SkillTreeWidget.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"


// Sets default values for this component's properties
USkillTreeComponent::USkillTreeComponent()
	:
	SkillTreeDT(nullptr), NumOfSkillPointsToAdd(0), DebugOn(false),
    SkillTreeMappingContext(nullptr),
    ToggleSTAction(nullptr),
    AddSTPointsAction(nullptr),
    UnlockSTSkillAction(nullptr),
	NavigateSTAction(nullptr),
	Character(nullptr),
    SkillTreeWidget(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillTreeComponent::BeginPlay()
{
	Super::BeginPlay();


	Character = Cast<AUTAD_UI_FPSCharacter>(GetOwner());
	if(!Character)
	{
		UE_LOG(LogTemp, Error, TEXT("SkillTreeCmp in a character that isnt type UTAD_UI_FPSCharacter"));
	}
	
	// ...
	LoadSkillTree(DTRowNameToInit);
	if(SkillTreeWidgetType) CreateSkillTreeUI();
	SetupInput();
}


// Called every frame
void USkillTreeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillTreeComponent::LoadSkillTree(FName RowName)
{
	if (!SkillTreeDT)
	{
		if(DebugOn) UE_LOG(LogTemp, Warning, TEXT("SkillTreeDataTable is null!"));
		return;
	}

	// Look up the row by name
	FSkillTree* Row = SkillTreeDT->FindRow<FSkillTree>(RowName, TEXT("SkillTree Lookup"));
	
	if (Row)
	{
		// Store the row data in SkillTree
		CurrentSkillTree = *Row;
		if(DebugOn) UE_LOG(LogTemp, Log, TEXT("Successfully loaded skill tree: %s"), *RowName.ToString());
	}
	else
	{
		if(DebugOn) UE_LOG(LogTemp, Warning, TEXT("Could not find row with name %s"), *RowName.ToString());
	}
}

void USkillTreeComponent::CreateSkillTreeUI()
{
	SkillTreeWidget = CreateWidget<USkillTreeWidget>(GetWorld(), SkillTreeWidgetType);
	for (const FTreeBranch& Branch : CurrentSkillTree.SkillBranches)
	{
		SkillTreeWidget->AddBranch(Branch);
	}
}


void USkillTreeComponent::SetupInput()
{
	AController* Controller = Cast<ACharacter>(GetOwner())->GetController();

	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(SkillTreeMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Toggle SkillTree
			EnhancedInputComponent->BindAction(ToggleSTAction, ETriggerEvent::Started, this, &USkillTreeComponent::ShowSkillTree);
		
			//Add Skill Points to Player 
			EnhancedInputComponent->BindAction(AddSTPointsAction, ETriggerEvent::Triggered, this, &USkillTreeComponent::AddSkillPoints);
			
			// Start Unlocking skill
			EnhancedInputComponent->BindAction(UnlockSTSkillAction, ETriggerEvent::Started, this, &USkillTreeComponent::StartUnlockingSkill);

			// Complete Unlocking skill
			EnhancedInputComponent->BindAction(UnlockSTSkillAction, ETriggerEvent::Completed, this, &USkillTreeComponent::CompleteUnlockingSkill);

			// Cancel Unlocking skill
			EnhancedInputComponent->BindAction(UnlockSTSkillAction, ETriggerEvent::Canceled, this, &USkillTreeComponent::StopUnlockingSkill);
			
			// Navigate Action
			EnhancedInputComponent->BindAction(NavigateSTAction, ETriggerEvent::Started, this, &USkillTreeComponent::NavigateTree);
		}
	}
}

void USkillTreeComponent::ShowSkillTree()
{
	if(!skillTreeInScreen)
	{
		SkillTreeWidget->AddToViewport(1);
		skillTreeInScreen = true;
	}
	else
	{
		SkillTreeWidget->RemoveFromParent(); 
		skillTreeInScreen = false;
	}
}

void USkillTreeComponent::AddSkillPoints()
{
	if(Character)
	{
		Character->SetSkillPoints(Character->GetSkillPoints() + NumOfSkillPointsToAdd);
	}
}

void USkillTreeComponent::StartUnlockingSkill()
{
	if(!skillTreeInScreen) return;
}

void USkillTreeComponent::CompleteUnlockingSkill()
{
	if(!skillTreeInScreen) return;
}

void USkillTreeComponent::StopUnlockingSkill()
{
	
}

void USkillTreeComponent::NavigateTree(const FInputActionValue& Value)
{
	if(!skillTreeInScreen) return;
	
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if(MovementVector.X > 0) // Up
	{
		SkillTreeWidget->UpdateVerticalIndex(-1);
	}
	else if(MovementVector.X < 0) // Down
	{
		SkillTreeWidget->UpdateVerticalIndex(1);
	}
	if(MovementVector.Y < 0) // Left
	{
		SkillTreeWidget->UpdateHorizontalIndex(-1); 
	}
	else if(MovementVector.Y > 0) // Right
	{
		SkillTreeWidget->UpdateHorizontalIndex(1); 
	}

	if(MovementVector.X != 0)
	{
		
	}

	if(MovementVector.Y != 0)
	{
		
	}
}

