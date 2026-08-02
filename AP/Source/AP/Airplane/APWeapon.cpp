// Fill out your copyright notice in the Description page of Project Settings.


#include "APWeapon.h"
#include "APProjectile.h"

AAPWeapon::AAPWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAPWeapon::BeginPlay()
{
	Super::BeginPlay();

	InitializePool();
}

void AAPWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer = FMath::Clamp(Timer - DeltaTime, 0, CoolTime);

	// 일정 시간 간격으로 연사 가능
	if (bCanFire)
	{
		if (Timer <= 0.f)
		{
			Fire();
			Timer = CoolTime;
		}
	}
}

void AAPWeapon::OnStartFire()
{
	bCanFire = true;
}

void AAPWeapon::OnStopFire()
{
	bCanFire = false;
}

void AAPWeapon::Fire()
{
	if (TObjectPtr<AAPProjectile> Projectile = GetAvailableProjectile()) 
	{
		Projectile->ActivateProjectile(GetActorTransform());
	}
}

void AAPWeapon::InitializePool()
{
	if (!ProjectileClass) { return; }

	for (int32 i = 0; i < InitialPoolSize; ++i)
	{
		TObjectPtr<AAPProjectile> Projectile = GetWorld()->SpawnActor<AAPProjectile>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);

		if (Projectile)
		{
#if WITH_EDITOR
			Projectile->SetFolderPath(TEXT("Projectiles"));
#endif

			Projectile->DeactivateProjectile();
			ProjectilePool.Add(Projectile);
		}
	}
}

TObjectPtr<AAPProjectile> AAPWeapon::GetAvailableProjectile()
{
	for (TObjectPtr<AAPProjectile> Projectile : ProjectilePool)
	{
		if (IsValid(Projectile) && !Projectile->IsActive())
		{
			return Projectile;
		}
	}

	return nullptr;
}