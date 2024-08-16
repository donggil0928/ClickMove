// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMovePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "ClickMouseCharacter.h"

AClickMovePlayerController::AClickMovePlayerController()
{
	bShowMouseCursor = true;
	bClickRightMouse = false; //
	MyChar = nullptr; //
}

 void AClickMovePlayerController::BeginPlay()
 {
 	Super::BeginPlay();
	
 	APawn* MyPawn = GetPawn();
	
	AClickMouseCharacter* Char = Cast<AClickMouseCharacter>(MyPawn);
	if (Char)
	{
		MyChar = Char;
	}
	else
	{
		MyChar = nullptr;
	}
 }

void AClickMovePlayerController::InputRightMouseButtonPressed()
{
	bClickRightMouse = true;
}

void AClickMovePlayerController::InputRightMouseButtonReleased()
{
	bClickRightMouse = false;
}

void AClickMovePlayerController::SetNewDestination( const FVector Destination)
{
	if (MyChar)
	{
		MyChar->SetnewDestination(this, Destination);
	}
}

void AClickMovePlayerController::MoveToMouseCursor()
{
	if (!MyChar) return;
	
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
		SetNewDestination(Hit.ImpactPoint);
}

void AClickMovePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("RightClick", IE_Pressed, this, &AClickMovePlayerController::InputRightMouseButtonPressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &AClickMovePlayerController::InputRightMouseButtonReleased);

	
	
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AClickMovePlayerController::OnLeftClickPressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AClickMovePlayerController::OnLeftClickReleased);
	
	InputComponent->BindAction<FUseSkillDelegate>("QSkill", IE_Pressed, this, &AClickMovePlayerController::UseSkill, 0);	// 가독성을 위해 ENUM 타입으로 수정 고려, EX) Skills[ESkillKey::Key_Q].GetDefaultObject()
	//InputComponent->BindAction<FUseSkillDelegate>("WSkill", IE_Pressed, this, &AClickMovePlayerController::UseSkill, 1);	// �������� ���� ENUM Ÿ������ ���� ���, EX) Skills[ESkillKey::Key_Q].GetDefaultObject()
	//InputComponent->BindAction<FUseSkillDelegate>("ESkill", IE_Pressed, this, &AClickMovePlayerController::UseSkill, 2);	// �������� ���� ENUM Ÿ������ ���� ���, EX) Skills[ESkillKey::Key_Q].GetDefaultObject()
	//InputComponent->BindAction<FUseSkillDelegate>("RSkill", IE_Pressed, this, &AClickMovePlayerController::UseSkill, 3);	// �������� ���� ENUM Ÿ������ ���� ���, EX) Skills[ESkillKey::Key_Q].GetDefaultObject()
    	
}

void AClickMovePlayerController::OnLeftClickPressed()
{
	if (MyChar)
	{
		MyChar->AttackDown();
	}
}
void AClickMovePlayerController::OnLeftClickReleased()
{
	if (MyChar)
	{
		MyChar->AttackUp();
	}
}

void AClickMovePlayerController::UseSkill(int SkillIndex)
{
	if (!MyChar) return;
	
	AClickMouseCharacter* Char = Cast<AClickMouseCharacter>(GetPawn());
	Char->UseSkill(SkillIndex);
}

void AClickMovePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bClickRightMouse)
		MoveToMouseCursor();
}
