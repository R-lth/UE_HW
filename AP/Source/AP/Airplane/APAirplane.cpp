// Fill out your copyright notice in the Description page of Project Settings.


#include "APAirplane.h"

// Sets default values
AAPAirplane::AAPAirplane()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	// 정적 메시
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	PropellerLeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropellerLeftMesh"));
	PropellerLeftMesh->SetupAttachment(BodyMesh);

	PropellerRightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropellerRightMesh"));
	PropellerRightMesh->SetupAttachment(BodyMesh);

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

}

// Called to bind functionality to input
void AAPAirplane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

