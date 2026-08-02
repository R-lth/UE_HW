// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "APAirplane.generated.h"

class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UFloatingPawnMovement;

UCLASS()
class AP_API AAPAirplane : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAPAirplane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnFire();
	void OnMove();
	void OnLook(const FInputActionValue& Value);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LeftMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> RightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFloatingPawnMovement> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MaxSpeed = 1200.f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float Acceleration = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float Deceleration = 400.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TObjectPtr<UInputAction> IA_Fire;

};
