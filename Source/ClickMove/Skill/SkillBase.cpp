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
		//��� ��ų���� �������� �۵��ϴ� ���
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
