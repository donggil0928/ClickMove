// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMovePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "ClickMouseCharacter.h"

AClickMovePlayerController::AClickMovePlayerController()
{
	bShowMouseCursor = true;
}

void AClickMovePlayerController::InputRightMouseButtonPressed()
{
	bClickRightMouse = true;
}

void AClickMovePlayerController::InputRightMouseButtonReleased()
{
	bClickRightMouse = false;
}

void AClickMovePlayerController::SetnewDestination(const FVector Destination)
{
	APawn* const MyPawn = GetPawn();

	if (MyPawn)
	{
		// 공격 중 캐릭터 이동 제어 
		AClickMouseCharacter* Char = Cast<AClickMouseCharacter>(MyPawn);
		if (Char->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
		{
			return;
		}

		float const Distance = FVector::Dist(Destination, MyPawn->GetActorLocation());
		if (Distance > 120.0f)
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
	}
}

void AClickMovePlayerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
		SetnewDestination(Hit.ImpactPoint);
}

void AClickMovePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("RightClick", IE_Pressed, this, &AClickMovePlayerController::InputRightMouseButtonPressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &AClickMovePlayerController::InputRightMouseButtonReleased);
}

void AClickMovePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bClickRightMouse)
		MoveToMouseCursor();
}
