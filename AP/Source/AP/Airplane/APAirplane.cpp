// Fill out your copyright notice in the Description page of Project Settings.


#include "APAirplane.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

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

	// Pawn 기준 움직임 컴포넌트
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	// 회전 
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArm->bUsePawnControlRotation = false;
	Camera->bUsePawnControlRotation = false;
}

void AAPAirplane::BeginPlay()
{
	Super::BeginPlay();
	
}

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

	// 비행기 전진 이동
	AddMovementInput(GetActorForwardVector(), Boost);
}

void AAPAirplane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	TObjectPtr<UEnhancedInputComponent> UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (UIC) 
	{
		UIC->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AAPAirplane::OnBoost);
		UIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAPAirplane::OnMove);
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AAPAirplane::OnFire);
	}
}

void AAPAirplane::OnBoost(const FInputActionValue& Value)
{
	Boost = Value.Get<float>();
}

void AAPAirplane::OnMove(const FInputActionValue& Value)
{
	FVector2D Dir = Value.Get<FVector2D>();

	// Pitch
	AddActorLocalRotation(FRotator(Dir.X, 0, 0) * 60 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
	// Roll
	AddActorLocalRotation(FRotator(0, 0, Dir.Y) * 60 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
}

void AAPAirplane::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Test"));
}

