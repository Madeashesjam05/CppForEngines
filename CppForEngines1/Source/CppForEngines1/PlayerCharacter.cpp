#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::AMyCharacter()
{
	// Let controller yaw rotate the character (optional depending on your design)
	bUseControllerRotationYaw = true;

	// Create the camera boom (spring arm)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);                  // attach to capsule root
	CameraBoom->TargetArmLength = 300.0f;                       // camera distance
	CameraBoom->bUsePawnControlRotation = true;                 // rotate arm based on controller

	// Create the camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // attach to end of boom
	FollowCamera->bUsePawnControlRotation = false;              // camera does not rotate relative to arm

	// Character movement settings (optional)
	GetCharacterMovement()->bOrientRotationToMovement = false;  // don't rotate toward movement automatically
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Movement axes (if you have them)
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::AddMovementInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayerCharacter::AddMovementInput);

	// Look / Turn
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}


