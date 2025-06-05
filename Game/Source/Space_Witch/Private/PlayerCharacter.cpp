// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Sets up the input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(WitchMappingContext, 0);
		}
	}
}

// Move Functionality
// TODO: Make Value move player forward, backward, left and right
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector IAValue = Value.Get<FVector>();

	// [LogCategory], [LogVerbiosity], TEXT(), value
	UE_LOG(LogTemp, Log, TEXT("Move function value: %s"), *IAValue.ToString());

	FVector ForwardVector = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	AddMovementInput(ForwardVector, IAValue.X);
	AddMovementInput(RightVector, IAValue.Y);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Binds the input action to the function
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	}
}

