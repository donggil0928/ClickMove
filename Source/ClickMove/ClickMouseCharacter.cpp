// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMouseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Animation/AnimInstance.h"

#include "Skill/SkillBase.h"

// Sets default values
AClickMouseCharacter::AClickMouseCharacter()
{
	bComboAttackDown = false;
	bComboAttacking = false;
	bComboAttackNext = false;
	ComboAttackNumber = 0;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-30.0f, 45.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	CameraComponent->bUsePawnControlRotation = false;

	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);

	CameraComponent->SetOrthoWidth(2048.0f);

	EquippedSkills.SetNum(4);
}

// Called when the game starts or when spawned
void AClickMouseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AClickMouseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AClickMouseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &AClickMouseCharacter::AttackDown);
	PlayerInputComponent->BindAction("LeftClick", IE_Released, this, &AClickMouseCharacter::AttackUp);

	//------------------스킬 사용 관련------------------
	PlayerInputComponent->BindAction("QSkill", IE_Pressed, this, &AClickMouseCharacter::SkillAssignQ);
	PlayerInputComponent->BindAction("WSkill", IE_Pressed, this, &AClickMouseCharacter::SkillAssignW);
	PlayerInputComponent->BindAction("ESkill", IE_Pressed, this, &AClickMouseCharacter::SkillAssignE);
	PlayerInputComponent->BindAction("RSkill", IE_Pressed, this, &AClickMouseCharacter::SkillAssignR);
	//-------------------------------------------------
}

void AClickMouseCharacter::AttackDown()
{
	// 이동 중 캐릭터 공격 제어
	GetCharacterMovement()->StopActiveMovement();
	
	
	UE_LOG(LogTemp, Warning, TEXT("AttackDown 함수 ... "));
	bComboAttackDown = true;

	if (bComboAttacking == false)
	{
		Attack();
	}
	else if (bComboAttacking == true)
	{
		bComboAttackNext = true;
	}
}

void AClickMouseCharacter::AttackUp()
{
	bComboAttackDown = false;
}

void AClickMouseCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack 함수 ... "));
	bComboAttackDown = true;

	UAnimInstance* AnimaInstance = GetMesh()->GetAnimInstance();

	if (!AnimaInstance || !comboMontage) return;

	bComboAttacking = true;
	const char* comboList[] = { "combo1", "combo2", "combo3", "combo4"};

	if (ComboAttackNumber >= 4)
		ComboAttackNumber = 0;
	UE_LOG(LogTemp, Warning, TEXT("                 콤보공격 ComboAttack%d"), ComboAttackNumber);

	AnimaInstance->Montage_Play(comboMontage, 1.5f);
	AnimaInstance->Montage_JumpToSection(FName(comboList[ComboAttackNumber]), comboMontage);
}

void AClickMouseCharacter::AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("ComboAttackEnd 함수 ... "));
	bComboAttacking = false;
	ComboAttackNumber = 0;
}

void AClickMouseCharacter::AttackCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("ComboAttackCheck 함수 ... "));

	if (bComboAttackNext == true)
	{
		ComboAttackNumber += 1;
		bComboAttackNext = false;
		Attack();
	}
}

void AClickMouseCharacter::SkillAssignQ()
{
	if (!EquippedSkills[0].IsCooldownActive())
	{
		EquippedSkills[0].Activate(this);
		StartCooldown(EquippedSkills[0]);
	}
}

void AClickMouseCharacter::SkillAssignW()
{
	EquippedSkills[1].Activate(this);
}

void AClickMouseCharacter::SkillAssignE()
{
	EquippedSkills[2].Activate(this);
}

void AClickMouseCharacter::SkillAssignR()
{
	EquippedSkills[3].Activate(this);
}

void AClickMouseCharacter::StartCooldown(FSkillData CurrentSkill)
{
	CurrentSkill.ActivateCooldown();
	GetWorldTimerManager().SetTimer(CooldownHandle, &EndCooldown(CurrentSkill), CurrentSkill.Cooldown);
}

void AClickMouseCharacter::EndCooldown(FSkillData CurrentSkill)
{
	CurrentSkill.DisabledCooldown();
}
