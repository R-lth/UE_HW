// Fill out your copyright notice in the Description page of Project Settings.


#include "APProjectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h" 
#include "Kismet/GameplayStatics.h" 

// Sets default values
AAPProjectile::AAPProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->InitCapsuleSize(5.f, 30.f);
	RootComponent = Collider;

	// 정적 메쉬
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	// 움직임
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->SetUpdatedComponent(Collider); // 움직임에 맞춰 충돌체를 이동시킴
	Movement->InitialSpeed = 3000.f;
	Movement->MaxSpeed = 3000.f;
	Movement->bRotationFollowsVelocity = true; // 이동 방향(속도)에 따라 회전 방향을 반영시킴
	Movement->bShouldBounce = true; // 반사
	Movement->Bounciness = 0.3f; // 반발 계시(반사 관련)

}

// Called when the game starts or when spawned
void AAPProjectile::BeginPlay()
{
	Super::BeginPlay();

	// 충돌 이벤트 관련 동적 델리게이트에 수신 함수(Callback 함수) 연동
	Collider->OnComponentHit.AddDynamic(this, &AAPProjectile::ProcessHit);
}

// Called every frame
void AAPProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 프로젝타일의 속도를 발사 방향으로 초기화시키는 함수입니다.
void AAPProjectile::FireInDirection(const FVector& ShootDirection)
{
	Movement->Velocity = ShootDirection * Movement->InitialSpeed;
}

void AAPProjectile::ProcessHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ImpactEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Hit.ImpactPoint);
	}

	Destroy();
}