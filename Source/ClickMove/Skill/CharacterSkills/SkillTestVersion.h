// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "SkillTestVersion.generated.h"

/**
 * 
 */
UCLASS()
class CLICKMOVE_API USkillTestVersion : public USkillBase
{
	GENERATED_BODY()
	
public:
	USkillTestVersion();

public:
	virtual void ActivateSkill(AActor* Owner) override;
};
