// Fill out your copyright notice in the Description page of Project Settings.


#include "APAirplane.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AAPAirplane::AAPAirplane()
{
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	// 정적 메시
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftMesh"));
	LeftMesh->SetupAttachment(BodyMesh);
	LeftMesh->SetRelativeLocation(FVector(38.f, -20.f, 0.f));

	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightMesh"));
	RightMesh->SetupAttachment(BodyMesh);
	RightMesh->SetRelativeLocation(FVector(38.f, 20.f, 0.f));

	// TPS 카메라
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 180.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AAPAirplane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPAirplane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 프로펠러 로컬 회전
	if (LeftMesh) 
	{
		LeftMesh->AddLocalRotation(FRotator(0, 0, 1440.f * DeltaTime));
	}
	if (RightMesh) 
	{
		RightMesh->AddLocalRotation(FRotator(0, 0, 1440.f * DeltaTime));
	}
}

void AAPAirplane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

