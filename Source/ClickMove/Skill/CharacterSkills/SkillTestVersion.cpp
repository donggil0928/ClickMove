// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/CharacterSkills/SkillTestVersion.h"

USkillTestVersion::USkillTestVersion()
{
	Cooldown = 3.0f;
}

void USkillTestVersion::ActivateSkill(AActor* Owner)
{
	if (!IsCooldownActive())
	{
		Super::ActivateSkill(Owner);

		//이 스킬의 기능을 작성
		UE_LOG(LogTemp, Log, TEXT("Test Skill Active!"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Skill is Cooldown!"));
	}
}
