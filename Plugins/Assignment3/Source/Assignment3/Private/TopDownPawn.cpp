// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATopDownPawn::ATopDownPawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 700.0f;
	SpringArm->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, SpringArm->SocketName);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));
}

// Called when the game starts or when spawned
void ATopDownPawn::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void ATopDownPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATopDownPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	check(EIC);

	MoveAction = NewObject<UInputAction>(this, TEXT("Pawn Movement"));
	MoveAction->ValueType = EInputActionValueType::Axis2D;
	LookAction = NewObject<UInputAction>(this, TEXT("Mouse Movement"));
	LookAction->ValueType = EInputActionValueType::Axis1D;

	PawnMappingContext = NewObject<UInputMappingContext>(this, TEXT("Pawn Mapping Context"));

	FEnhancedActionKeyMapping& MoveForwardKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::W);

	FEnhancedActionKeyMapping& MoveBackwardKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::S);
	UInputModifierNegate* MoveActionModifierNegate = NewObject<UInputModifierNegate>(this, TEXT("Negate Modifier"));
	MoveBackwardKeyMapping.Modifiers.Add(MoveActionModifierNegate);

	FEnhancedActionKeyMapping& MoveRightKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::D);
	UInputModifierSwizzleAxis* MoveActionModifierSwizzleAxis = NewObject<UInputModifierSwizzleAxis>(this, TEXT("Swizzle Axis YXZ"));
	MoveActionModifierSwizzleAxis->Order = EInputAxisSwizzle::YXZ;
	MoveRightKeyMapping.Modifiers.Add(MoveActionModifierSwizzleAxis);

	FEnhancedActionKeyMapping& MoveLeftKeyMapping = PawnMappingContext->MapKey(MoveAction, EKeys::A);
	MoveLeftKeyMapping.Modifiers.Add(MoveActionModifierNegate);
	MoveLeftKeyMapping.Modifiers.Add(MoveActionModifierSwizzleAxis);

	FEnhancedActionKeyMapping& ScrollWheelMapping = PawnMappingContext->MapKey(LookAction, EKeys::MouseWheelAxis);
	UInputModifierNegate* LookActionModifierNegate = NewObject<UInputModifierNegate>(this, TEXT("Mouse Negate Modifier"));
	ScrollWheelMapping.Modifiers.Add(LookActionModifierNegate);

	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATopDownPawn::PawnMovement);
	EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATopDownPawn::ScrollWheelMovement);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<APlayerController>(GetController())->GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PawnMappingContext, 0);
}

void ATopDownPawn::PawnMovement(const FInputActionValue& ActionValue) {
	FVector2D MoveScale = ActionValue.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MoveScale.X);
	AddMovementInput(GetActorRightVector(), MoveScale.Y);
}

void ATopDownPawn::ScrollWheelMovement(const FInputActionValue& ActionValue) {
	float ScrollWheelScale = ActionValue.Get<FInputActionValue::Axis1D>();

	if (SpringArm->TargetArmLength >= 500.f) {
		float NewArmLength = SpringArm->TargetArmLength + (ScrollWheelScale*25);
		SpringArm->TargetArmLength = NewArmLength;

		UE_LOG(LogTemp, Warning, TEXT("NewArmLength: %f"), NewArmLength);
	}
	//else {
	//	float SinAngle = 
	//}
}

