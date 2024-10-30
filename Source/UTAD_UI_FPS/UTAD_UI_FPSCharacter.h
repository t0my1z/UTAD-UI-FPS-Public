// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UTAD_UI_FPSCharacter.generated.h"

class USkillTreeComponent;
class USplashArtScreen;
class UInputComponent;
class UInputMappingContext;
class UInputAction;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UTP_WeaponComponent;
struct FInputActionValue;

class UPlayerHUD;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnealthChanged, int, CurrentHealth, int, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamaged, float, HealthPercentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTotalBulletsChanged, int, TotalBullets);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillPointChanged, int, SkillPoints);

UCLASS(config=Game)
class AUTAD_UI_FPSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Weapon component that is attached */
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	UTP_WeaponComponent* AttachedWeaponComponent; 

	UPROPERTY(VisibleAnywhere, Category = SkillTree)
	USkillTreeComponent* SkillTreeComponent;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	
public:
	AUTAD_UI_FPSCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Current Health */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int Health = 100;

	/** Max Health */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int SkillPoints = 2; 
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnealthChanged HealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnDamaged OnDamaged;
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnTotalBulletsChanged OnTotalBulletsChanged;
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnSkillPointChanged OnSkillPointChanged;
	
	/** Counter for bullets in player (not in weapon) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	int TotalBullets = 100;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Debug)
	bool DebugOn;
	
#pragma region Getters & Setters
	
	/** Setter to set the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetHealth(int NewHealth);

	/** Getter for the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	int GetHealth();

	/** Setter to set the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetMaxHealth(int NewMaxHealth);

	/** Getter for the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	int GetMaxHealth();

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	/** Setter to set the int */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetTotalBullets(int NewTotalBullets);

	/** Getter for the int */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	int GetTotalBullets();
	
	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetSkillPoints(int newSkillPoints);

	UFUNCTION(BlueprintCallable, Category = Stats)
	int GetSkillPoints() const { return SkillPoints; }
	
#pragma endregion
	
	/** Function to add an amount of bullets to TotalBullets */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void AddBullets(int Bullets);

	UFUNCTION(BlueprintCallable, Category = Damage)
	void GetDamaged(int _inDamage);
	
	UPlayerHUD* GetPlayerHUD() const;
	
	void SetAttachedWeaponComponent(UTP_WeaponComponent* WeaponComponent);
	
	/****************************************************/
	/************************ UI ************************/
	/****************************************************/
	
	/** Widget Blueprints that will be used to create the instances */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UPlayerHUD> PlayerHUDWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<USplashArtScreen> SplashArtWidget;
	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	/** Returns AttachedWeaponComponent subobject **/
	UTP_WeaponComponent* GetAttachedWeaponComponent() const { return AttachedWeaponComponent; }

private:

	/****************************************************/
	/************************ UI ************************/
	/****************************************************/

	/** Instances that will be created and showed on viewport */
	UPROPERTY()
	UPlayerHUD* PlayerHUDInstance;
};

