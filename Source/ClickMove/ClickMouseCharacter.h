// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ClickMouseCharacter.generated.h"

UCLASS()
class CLICKMOVE_API AClickMouseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClickMouseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	bool bComboAttacking;
	bool bComboAttackDown;
	bool bComboAttackNext;
	int ComboAttackNumber;

	//UPROPERTY(EditAnywhere, Category = "ComboAttack", meta = (AllowPrivateAccess = "true"))
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "ComboAttack", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* comboMontage;	// 애니메이션 몽타주

	// 일반 공격
	UFUNCTION(BlueprintCallable)
	void AttackDown();	// 마우스 왼쪽 버튼 누름 - 일반 공격

	UFUNCTION(BlueprintCallable)
	void AttackUp();	// 마우스 왼쪽 버튼 해제 - 일반 공격 종료

	UFUNCTION(BlueprintCallable)
	void Attack();	// Combo 몽타주 Section 플레이

	UFUNCTION(BlueprintCallable)
	void AttackEnd();	// 노티파이 - combo 몽타주 Section 종료

	UFUNCTION(BlueprintCallable)
	void AttackCheck();	// combo Section 인덱스 증가

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

};
