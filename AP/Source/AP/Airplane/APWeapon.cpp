// Fill out your copyright notice in the Description page of Project Settings.


#include "APWeapon.h"
#include "APProjectile.h"

AAPWeapon::AAPWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAPWeapon::Tick(float DeltaTime)
{
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
	// todo. 오브젝트 풀링
	GetWorld()->SpawnActor<AAPProjectile>(ProjectileClass, GetActorTransform());
}
