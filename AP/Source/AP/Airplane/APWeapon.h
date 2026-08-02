// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "APWeapon.generated.h"

class AAPProjectile;

UCLASS()
class AP_API AAPWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AAPWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void OnStartFire();
	void OnStopFire();

private:
	void Fire();
	void InitializePool();
	TObjectPtr<AAPProjectile> GetAvailableProjectile();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class AAPProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
	int32 InitialPoolSize = 20;

	UPROPERTY()
	TArray<TObjectPtr<AAPProjectile>> ProjectilePool;

private:
	uint8 bCanFire : 1 = false;
	float CoolTime = 0.15f;
	float Timer = 0.f;
};
