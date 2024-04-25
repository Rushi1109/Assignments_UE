// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFirstPersonPawn::AFirstPersonPawn() : PawnMappingContext{ nullptr }, MoveAction{ nullptr }, LookAction{ nullptr }, MoveScale{ 1.0f }
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetCapsuleRadius(40);
	CapsuleComponent->SetCapsuleHalfHeight(90);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//CapsuleComponent->SetEnableGravity(true);
	//CapsuleComponent->SetSimulatePhysics(true);
	SetRootComponent(CapsuleComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bHiddenInGame = false;
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(CapsuleComponent);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

// Called when the game starts or when spawned
void AFirstPersonPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFirstPersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFirstPersonPawn::OnConstruction(const FTransform& Transform) {}

// Called to bind functionality to input
void AFirstPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	check(EIC);

	PawnMappingContext = NewObject<UInputMappingContext>(this);

	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	LookAction = NewObject<UInputAction>(this);
	LookAction->ValueType = EInputActionValueType::Axis2D;

	UInputModifierNegate* MoveActionModifierNegate = NewObject<UInputModifierNegate>();

	UInputModifierSwizzleAxis* SwizzleAxisModifier = NewObject<UInputModifierSwizzleAxis>();
	SwizzleAxisModifier->Order = EInputAxisSwizzle::YXZ;
	UInputModifierSwizzleAxis* SwizzleAxisModifierQE = NewObject<UInputModifierSwizzleAxis>();
	SwizzleAxisModifierQE->Order = EInputAxisSwizzle::ZYX;

	FEnhancedActionKeyMapping& MovementForwardKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::W);

	FEnhancedActionKeyMapping& MovementBackwardKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::S);
	MovementBackwardKeyMapping.Modifiers.Add(MoveActionModifierNegate);

	FEnhancedActionKeyMapping& MovementRightKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::D);
	MovementRightKeyMapping.Modifiers.Add(SwizzleAxisModifier);

	FEnhancedActionKeyMapping& MovementLeftKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::A);
	MovementLeftKeyMapping.Modifiers.Add(SwizzleAxisModifier);
	MovementLeftKeyMapping.Modifiers.Add(MoveActionModifierNegate);

	FEnhancedActionKeyMapping& MovementUpKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::E);
	MovementUpKeyMapping.Modifiers.Add(SwizzleAxisModifierQE);

	FEnhancedActionKeyMapping& MovementDownKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::Q);
	MovementDownKeyMapping.Modifiers.Add(SwizzleAxisModifierQE);
	MovementDownKeyMapping.Modifiers.Add(MoveActionModifierNegate);

	UInputModifierNegate* LookActionMouseModifierNegate = NewObject<UInputModifierNegate>();
	LookActionMouseModifierNegate->bX = false;
	LookActionMouseModifierNegate->bY = true;
	LookActionMouseModifierNegate->bZ = false;

	FEnhancedActionKeyMapping& LookActionMouseMapping = PawnMappingContext->MapKey(LookAction, EKeys::Mouse2D);
	LookActionMouseMapping.Modifiers.Add(LookActionMouseModifierNegate);

	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFirstPersonPawn::Move);
	EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFirstPersonPawn::LookAround);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	check(PlayerController)
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PawnMappingContext, 0);
}

void AFirstPersonPawn::LookAround(const FInputActionValue& ActionValue)
{
	FVector2D LookAxisValue = ActionValue.Get<FVector2D>();
	AddControllerYawInput(LookAxisValue.X);
	AddControllerPitchInput(LookAxisValue.Y);
}

void AFirstPersonPawn::Move(const FInputActionValue& ActionValue)
{
	FVector MovementInput = ActionValue.Get<FVector>();

	AddMovementInput(GetControlRotation().RotateVector(MovementInput), MoveScale);
}

