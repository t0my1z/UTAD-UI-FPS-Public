// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "UTAD_UI_FPSCharacter.h"
#include "UTAD_UI_FPSProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UTAD_UI_FPS_Enemy.h"

#include "Blueprint/UserWidget.h"
#include "UI/AmmoCounter.h"
#include "UI/Crosshair.h"
#include "UI/PlayerHUD.h"
#include "UI/ReloadBar.h"

#define RELOAD_TIME 1.f

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
	: ReloadTimer(0.f)
	, bIsReloading(false)
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UTP_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (bIsReloading)
	{
		ReloadTimer += DeltaTime;
	}

	EnemyDetected();
}

void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	if (CurrentNumBullets <= 0)
	{
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<AUTAD_UI_FPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	if(OnWeaponShot.IsBound()) OnWeaponShot.Broadcast();
	
	SetCurrentNumBullets(CurrentNumBullets -1);
}

void UTP_WeaponComponent::StartReload()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
	
	int playerBullets = Character->GetTotalBullets();
	playerBullets += CurrentNumBullets;

	if (playerBullets <= CurrentNumBullets || CurrentNumBullets == MagazineSize)
	{
		return;
	}

	bIsReloading = true;
	ReloadTimer = 0.f;

	if(OnReloadStart.IsBound()) OnReloadStart.Broadcast();
}

void UTP_WeaponComponent::CompleteReload()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	bIsReloading = false;

	int playerBullets = Character->GetTotalBullets();
	playerBullets += CurrentNumBullets;
	
	SetCurrentNumBullets(__min(MagazineSize, playerBullets));
	Character->SetTotalBullets(playerBullets - CurrentNumBullets);

	if(OnReloadEnd.IsBound()) OnReloadEnd.Broadcast();
}

void UTP_WeaponComponent::CancelReload()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	bIsReloading = false;
	if(OnReloadEnd.IsBound()) OnReloadEnd.Broadcast();
}

int UTP_WeaponComponent::GetMagazineSize()
{
	return MagazineSize;
}

void UTP_WeaponComponent::SetMagazineSize(int NewMagazineSize)
{
	MagazineSize = NewMagazineSize;
}

int UTP_WeaponComponent::GetCurrentNumBullets()
{
	return CurrentNumBullets;
}

void UTP_WeaponComponent::SetCurrentNumBullets(int NewCurrentNumBullets)
{
	CurrentNumBullets = NewCurrentNumBullets;

	if(OnWeaponReload.IsBound()) OnWeaponReload.Broadcast(CurrentNumBullets); 
}

void UTP_WeaponComponent::EnemyDetected()
{
	// Ensure the owner is valid
	if (AActor* Owner = GetOwner())
	{
		if (Character == nullptr || Character->GetController() == nullptr)	return;
		
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		
		const FRotator CameraRotation  = PlayerController->PlayerCameraManager->GetCameraRotation();
		FVector Start = GetOwner()->GetActorLocation() + CameraRotation .RotateVector(MuzzleOffset);; // Start position
		FVector ForwardVector = CameraRotation.Vector();// Forward direction
		FVector End = Start + (ForwardVector * TraceDistance); // End position (adjust TraceDistance as needed)

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		// Ignore the owner in the trace
		CollisionParams.AddIgnoredActor(Owner);

		// Perform the line trace
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, CollisionParams);

		// Check if we hit something
		if (bHit)
		{
			// Optionally draw debug line
			if(Debug)
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.f, 0, 1.0f);
			}
			
			// Check if the hit actor is an enemy
			if (AUTAD_UI_FPS_Enemy* HitEnemy = Cast<AUTAD_UI_FPS_Enemy>(HitResult.GetActor()))
			{
				if(!enemyDetected)
				{
					enemyDetected = true;
					if(OnEnemyTargeted.IsBound()) OnEnemyTargeted.Broadcast(true);
				}
				
				if(Debug) UE_LOG(LogTemp, Log, TEXT("Enemy detected: %s"), *HitEnemy->GetName());
			}
			else
			{
				if(enemyDetected)
				{
					enemyDetected = false;
					if(OnEnemyTargeted.IsBound()) OnEnemyTargeted.Broadcast(false);
				}
				
				if(Debug)UE_LOG(LogTemp, Log, TEXT("No enemy detected."));
			}
		}
		else
		{
			if(enemyDetected)
			{
				enemyDetected = false;
				if(OnEnemyTargeted.IsBound()) OnEnemyTargeted.Broadcast(false);
			}
			if(Debug) UE_LOG(LogTemp, Log, TEXT("No enemy detected."));
		}
	}
}

void UTP_WeaponComponent::AttachWeapon(AUTAD_UI_FPSCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	
	if (Character == nullptr || Character->GetHasRifle())
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	Character->SetAttachedWeaponComponent(this);
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);
	
	Character->GetPlayerHUD()->GetCrosshairUI()->SetupWeaponCmp(this);
	Character->GetPlayerHUD()->GetAmmoCounterUI()->SetupWeaponCmp(this); 
	Character->GetPlayerHUD()->GetReloadBarUI()->SetupWeaponCmp(this); 

	Debug = Character->DebugOn;
	
	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);

			// StartReload
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &UTP_WeaponComponent::StartReload);

			// CompleteReload
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Completed, this, &UTP_WeaponComponent::CompleteReload);

			// CancelReload
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Canceled, this, &UTP_WeaponComponent::CancelReload);

			for (TObjectPtr<UInputTrigger> Element : ReloadAction->Triggers)
			{
				if(Element.IsA(UInputTriggerHold::StaticClass()))
				{
					UInputTriggerHold* HoldTrigger = Cast<UInputTriggerHold>(Element);
					if(HoldTrigger)
					{
						ReloadTime = HoldTrigger->HoldTimeThreshold;
					}
				}
			}
		}
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}