// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "APWeapon.generated.h"

/**
 * 
 */
UCLASS()
class AP_API AAPWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AAPWeapon();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void OnStartFire();
	void OnStopFire();

private:
	void Fire();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class AAPProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FVector MuzzleOffset;

private:
	uint8 bCanFire : 1 = false;
	float CoolTime = 0.15f;
	float Timer = 0.f;
};
