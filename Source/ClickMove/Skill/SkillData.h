// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CLICKMOVE_API USkillData : public UObject
{
	GENERATED_BODY()
	
public:
	USkillData();

	void Use(class AClickMouseCharacter* player);
	void StartCooldown();
	void EndCooldown();

public:	// ��ų�� �ʿ��� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name; // ��ų �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;	// ��ų ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;	// ��ų�� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;	// ��ų�� ����(��Ÿ�)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Cost;	// ��ų�� �ڽ�Ʈ, ��� �� ��� ������ ���� �ǹ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondToCooldown;	// ��ų�� ��Ÿ��
	uint8 bIsCooldown:1;
	FTimerHandle CooldownTimerHandle;

	// �Ʒ��� ���� ���⿡ ��� �� �� ���� ������
	//Transform CurrentCharacterPos;
	//Vector2 CurrentMousePos;
	//int32 MaxHp;
	//int32 CurrentHp;
	//int32 CharacterAtkPower;
	//int32 CharacterMovementSpeed;
	//int32 RegenHpPerSecond;
	//int32 CurrentMadness;
	/*
	* �߰��� �ʿ��� ����(��ȹ ȸ�� �� �����ؾ� �� �κ�)
		��ų ���Կ� ǥ�õ� ��ų �ؽ��� �̹���, 
		��ų ��� �� �ִϸ��̼�, 
		��ų ����Ʈ, 
		��ų�� ����(�ٰŸ�����, ���Ÿ�����, ����/����� ��),
		��ų�� ��ġ(Q,W,E,R),
		��ų Ȱ��ȭ ����(�������� ����°�),
		��ų�� �ְ� ����,
		...
	*/
};
