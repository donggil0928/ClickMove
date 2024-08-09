// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMouseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Animation/AnimInstance.h"

#include "Skill/SkillData.h"

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

	//------------------��ų ��� ����------------------
	Skills.SetNum(4);	// ĳ���Ϳ��� �Ҵ�� ��ų�� 4��(�迭�� ũ�� ����)
	//-------------------------------------------------
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


	//------------------��ų ��� ����------------------
	
	PlayerInputComponent->BindAction<FUseSkillDelegate>("QSkill", IE_Pressed, this, &AClickMouseCharacter::UseSkill, Skills[0].GetDefaultObject());	// �������� ���� ENUM Ÿ������ ���� ���, EX) Skills[ESkillKey::Key_Q].GetDefaultObject()
	//PlayerInputComponent->BindAction<FUseSkillDelegate>("WSkill", IE_Pressed, this, &AClickMouseCharacter::UseSkill, Skills[1].GetDefaultObject());

	//-------------------------------------------------
}
void AClickMouseCharacter::AttackDown()
{
	// �̵� �� ĳ���� ���� ����
	GetCharacterMovement()->StopActiveMovement();
	
	
	UE_LOG(LogTemp, Warning, TEXT("AttackDown �Լ� ... "));
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
	UE_LOG(LogTemp, Warning, TEXT("Attack �Լ� ... "));
	bComboAttackDown = true;

	UAnimInstance* AnimaInstance = GetMesh()->GetAnimInstance();

	if (!AnimaInstance || !comboMontage) return;

	bComboAttacking = true;
	const char* comboList[] = { "combo1", "combo2", "combo3", "combo4"};

	if (ComboAttackNumber >= 4)
		ComboAttackNumber = 0;
	UE_LOG(LogTemp, Warning, TEXT("                 �޺����� ComboAttack%d"), ComboAttackNumber);

	AnimaInstance->Montage_Play(comboMontage, 1.5f);
	AnimaInstance->Montage_JumpToSection(FName(comboList[ComboAttackNumber]), comboMontage);
}

void AClickMouseCharacter::AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("ComboAttackEnd �Լ� ... "));
	bComboAttacking = false;
	ComboAttackNumber = 0;
}

void AClickMouseCharacter::AttackCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("ComboAttackCheck �Լ� ... "));

	if (bComboAttackNext == true)
	{
		ComboAttackNumber += 1;
		bComboAttackNext = false;
		Attack();
	}
}
//------------------��ų ��� ����------------------

void AClickMouseCharacter::UseSkill(USkillData* SkillDataRef)
{
	SkillDataRef->Use(this);

	/*USkillData* Skill = Cast<USkillData>(SkillDataRef);
	if (Skill != nullptr) Skill->Use(this);
	else UE_LOG(LogTemp, Warning, TEXT("Skill Not Found"));*/
}

