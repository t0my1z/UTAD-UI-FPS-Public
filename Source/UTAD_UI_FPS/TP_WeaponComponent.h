// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AUTAD_UI_FPSCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyTargeted, bool, EnemyFound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponReload, int, NumOfBullets);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponShot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadState);


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTAD_UI_FPS_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AUTAD_UI_FPSProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Reload Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	float ReloadTimer;
	float ReloadTime; 
	
	/** Maximum number of times the player can shoot the weapon before reloading */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MagazineSize = 10;

	/** Number of bullets currently in the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int CurrentNumBullets = 0;

	//Distance to detect enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int TraceDistance = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool Debug = false;
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnEnemyTargeted OnEnemyTargeted;
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnWeaponShot OnWeaponShot;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnWeaponReload OnWeaponReload;
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnReloadState OnReloadStart;
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnReloadState OnReloadEnd;
	
	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AUTAD_UI_FPSCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	/** Start to reload the Weapon */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartReload();

	/** Reload the Weapon */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void CompleteReload();

	/** Reload the Weapon */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void CancelReload();

	/** Getter for MagazineSize */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	int GetMagazineSize();

	/** Setter for MagazineSize */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetMagazineSize(int NewMagazineSize);

	/** Getter for CurrentNumBullets */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	int GetCurrentNumBullets();

	/** Setter for CurrentNumBullets */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetCurrentNumBullets(int NewCurrentNumBullets);

	void EnemyDetected();
	
protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	UPROPERTY()
	AUTAD_UI_FPSCharacter* Character;


	bool bIsReloading;

	bool enemyDetected = false;
};
