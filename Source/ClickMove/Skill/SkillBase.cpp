// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillBase.h"

USkillBase::USkillBase()
{
	bIsOnCooldown = false;
}

void USkillBase::ActivateSkill(AActor* Owner)
{
	if (!bIsOnCooldown)
	{
		//모든 스킬에서 공통으로 작동하는 기능
		UE_LOG(LogTemp, Log, TEXT("Skill Activated!"));

		StartCooldown();
	}
}

bool USkillBase::IsCooldownActive() const
{
	return bIsOnCooldown;
}

void USkillBase::StartCooldown()
{
	bIsOnCooldown = true;
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &USkillBase::EndCooldown, Cooldown);
	}
}

void USkillBase::EndCooldown()
{
	UE_LOG(LogTemp, Log, TEXT("Cooldown End"));
	bIsOnCooldown = false;
}
