// Fill out your copyright notice in the Description page of Project Settings.


#include "APPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AAPPlayerController::BeginPlay()
{
	if (!IMC.IsNull() && IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			InputSystem->AddMappingContext(IMC.LoadSynchronous(), 0);
		}
	}
}
