// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Skill/SkillData.h"
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
	//��ųŰ(Q,W,E,R) �Է� �� �� ��ų�� �����Ͽ� ���ε��ϱ� ���� ��������Ʈ�� �Լ�
	DECLARE_DELEGATE_OneParam(FUseSkillDelegate, class USkillData*);
	void UseSkill(class USkillData* SkillDataRef);

};
