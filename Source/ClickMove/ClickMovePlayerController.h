// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Skill/SkillData.h"
#include "ClickMovePlayerController.generated.h"

class AClickMouseCharacter;

UCLASS()
class CLICKMOVE_API AClickMovePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AClickMovePlayerController();
	 virtual void BeginPlay() override;
	
protected:
	UPROPERTY()
	AClickMouseCharacter* MyChar; // UObject라 스마트 포인터가 아닌 UPROPERTY
	bool bClickRightMouse;
	
	void InputRightMouseButtonPressed();
	void InputRightMouseButtonReleased();
	void SetNewDestination(const FVector Destination);
	void MoveToMouseCursor();
	virtual void SetupInputComponent() override;
	void OnLeftClickPressed();
	void OnLeftClickReleased();
	void UseSkill(int SkillIndex);
	virtual void PlayerTick(float DeltaTime) override;
};
