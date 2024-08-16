// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Skill/SkillData.h"
#include "ClickMouseCharacter.generated.h"

class AClickMovePlayerController;

DECLARE_DELEGATE_OneParam(FUseSkillDelegate, int);

UCLASS()
class CLICKMOVE_API AClickMouseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClickMouseCharacter();
	void SetnewDestination(AClickMovePlayerController* _LogPlayerController, const FVector Destination) const;

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
	class UAnimMontage* comboMontage;	// �ִϸ��̼� ��Ÿ��

	// �Ϲ� ����
	UFUNCTION(BlueprintCallable)
	void AttackDown();	// ���콺 ���� ��ư ���� - �Ϲ� ����

	UFUNCTION(BlueprintCallable)
	void AttackUp();	// ���콺 ���� ��ư ���� - �Ϲ� ���� ����

	UFUNCTION(BlueprintCallable)
	void Attack();	// Combo ��Ÿ�� Section �÷���

	UFUNCTION(BlueprintCallable)
	void AttackEnd();	// ��Ƽ���� - combo ��Ÿ�� Section ����

	UFUNCTION(BlueprintCallable)
	void AttackCheck();	// combo Section �ε��� ����

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

//------------------��ų ��� ����------------------
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TArray<TSubclassOf<class USkillData>> Skills;	//ĳ���Ͱ� ���� ��ų �迭
	
public:
	//스킬(Q,W,E,R) 입력 시 각 스킬을 구분하여 바인딩하기
	void UseSkill(int skillIndex);
	
};
