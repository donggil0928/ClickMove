// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillData.generated.h"
/**
 * 
 */
class CLICKMOVE_API SkillData
{
public:
	SkillData();
	~SkillData();
};

UENUM(BlueprintType)
enum class ESkillPosition : uint8
{
	Q UMETA(DisplayName = "Skill Q"),
	W UMETA(DisplayName = "Skill W"),
	E UMETA(DisplayName = "Skill E"),
	R UMETA(DisplayName = "Skill R")
};

USTRUCT(Atomic, BlueprintType)
struct FSkillData
{
	GENERATED_USTRUCT_BODY()
	
public:
	FSkillData();

	void Activate(AActor* Owner);

	bool IsCooldownActive();
	void ActivateCooldown();
	void DisabledCooldown();

public:
	UPROPERTY(EditAnywhere)
	ESkillPosition SkillPositionEnum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DebugText;

private:
	bool bIsOnCooldown;
};
