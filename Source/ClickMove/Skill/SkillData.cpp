// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillData.h"
#include "ClickMouseCharacter.h"

USkillData::USkillData()
{
	Name = FText::FromString(TEXT("Skill_Name"));
	Description = FText::FromString(TEXT("Skill_Description"));
	CurrentLevel = 1;
	Range = 1.0f;
	Cost = 1;
	SecondToCooldown = 1.0f;
	bIsCooldown = false;
}

void USkillData::Use(AClickMouseCharacter* player)
{
	if (!bIsCooldown)
	{
		UE_LOG(LogTemp, Log, TEXT("%s is Activated!"), *Name.ToString());

		// �ش� �κп��� ��ų ��� �� �ִϸ��̼ǰ� ����Ʈ ���� ó��(����)
		//

		//StartCooldown();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is Now Cooldown!"), *Name.ToString());
	}
}

void USkillData::StartCooldown()
{
	bIsCooldown = true;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &USkillData::EndCooldown, SecondToCooldown, false); // this ȣ�� �� nullptr ���� �߻�, CDO�� ���� �Լ��� ȣ���ϴ� ���� ������ ����.
}

void USkillData::EndCooldown()
{
	bIsCooldown = false;
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
}
