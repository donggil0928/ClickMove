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
		// 스킬 데이터에 추가해야 하는 것들을 이용
		// 스킬을 사용했을 때의 애니메이션이나 데미지 계산 등을 함
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
