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

	// 컴포넌트
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftMesh"));
	LeftMesh->SetupAttachment(BodyMesh);
	LeftMesh->SetRelativeLocation(FVector(38.f, -20.f, 0.f));

	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightMesh"));
	RightMesh->SetupAttachment(BodyMesh);
	RightMesh->SetRelativeLocation(FVector(38.f, 20.f, 0.f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 180.f;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = MaxSpeed;
	Movement->Acceleration = Acceleration;
	Movement->Deceleration = Deceleration;

	ChildActorComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActorComp"));
	ChildActorComp->SetupAttachment(BodyMesh, FName(TEXT("SpawnSocket")));

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

	// 자식 액터
	ChildActor = Cast<AAPWeapon>(ChildActorComp->GetChildActor());
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
	if (bIsMove) 
	{
		AddMovementInput(GetActorForwardVector(), 1.f);
	}
}

void AAPAirplane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	TObjectPtr<UEnhancedInputComponent> UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (UIC) 
	{
		UIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAPAirplane::OnMove);
		UIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AAPAirplane::OnLook);
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AAPAirplane::OnStartFire);
		UIC->BindAction(IA_Fire, ETriggerEvent::Completed, this, &AAPAirplane::OnStopFire);
		UIC->BindAction(IA_Fire, ETriggerEvent::Canceled, this, &AAPAirplane::OnStopFire);
	}
}

void AAPAirplane::Configure(const float InMaxSpeed, const float InAcceleration, const float InDeceleration)
{
	MaxSpeed = InMaxSpeed;
	Acceleration = InAcceleration;
	Deceleration = InDeceleration;
}

void AAPAirplane::OnMove()
{
	bIsMove = static_cast<uint8>(!bIsMove);
}

void AAPAirplane::OnLook(const FInputActionValue& Value)
{
	FVector2D Dir = Value.Get<FVector2D>();

	// Pitch
	AddActorLocalRotation(FRotator(Dir.X, 0, 0) * 60 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
	// Roll
	AddActorLocalRotation(FRotator(0, 0, Dir.Y) * 60 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
}

void AAPAirplane::OnStartFire()
{
	if (ChildActor) 
	{
		ChildActor->OnStartFire();
	}
}

void AAPAirplane::OnStopFire()
{
	if (ChildActor) 
	{
		ChildActor->OnStopFire();
	}
}

