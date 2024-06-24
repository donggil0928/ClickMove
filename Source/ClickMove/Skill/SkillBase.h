// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CLICKMOVE_API USkillBase : public UObject
{
	GENERATED_BODY()
	
public:
	USkillBase();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float Cooldown;
	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual void ActivateSkill(AActor* Owner);
	UFUNCTION(BlueprintCallable, Category = "Skill")
	bool IsCooldownActive() const;

private:
	bool bIsOnCooldown;
	FTimerHandle CooldownTimerHandle;
	void StartCooldown();
	void EndCooldown();
};
