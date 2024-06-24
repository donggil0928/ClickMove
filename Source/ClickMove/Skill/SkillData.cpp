// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillData.h"

SkillData::SkillData()
{
}

SkillData::~SkillData()
{
}

FSkillData::FSkillData()
{
	bIsOnCooldown = false;
}

void FSkillData::Activate(AActor* Owner)
{
	if(!bIsOnCooldown)
	{
		UE_LOG(LogTemp, Log, TEXT("Skill %s Activated!"), *DebugText);
		// ��ų �����Ϳ� �߰��ؾ� �ϴ� �͵��� �̿�
		// ��ų�� ������� ���� �ִϸ��̼��̳� ������ ��� ���� ��
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Skill %s is Cooldown."), *DebugText);
	}
}

bool FSkillData::IsCooldownActive()
{
	return bIsOnCooldown;
}

void FSkillData::ActivateCooldown()
{
	bIsOnCooldown = true;
}

void FSkillData::DisabledCooldown()
{
	bIsOnCooldown = false;
}
