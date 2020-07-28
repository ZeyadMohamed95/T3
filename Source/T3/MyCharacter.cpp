// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyActor.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 300.0f;
	CameraSpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(CameraSpringArm);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	

}



// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (PLayerWidgetClass != nullptr) {
		PlayerHealth = CreateWidget(GetWorld(), PLayerWidgetClass);
		PlayerHealth->AddToViewport();
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AMyCharacter::RestartGame);
}

void AMyCharacter::MoveForward(float Value)
{
	if (!IsDead)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (!IsDead)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}
void AMyCharacter::Turn(float Amount)
{
	AddControllerYawInput(Amount);
}
void AMyCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}
void AMyCharacter::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
void AMyCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AMyActor* actor = Cast<AMyActor>(OtherActor))
	{
		if (actor->status ==Status::Damage)
		{
			HealthPoints -= actor->HDAmount;
			if (HealthPoints <= 0)
			{
				HealthPoints = 0;
				IsDead = true;
				GetMesh()->SetSimulatePhysics(true);
			}
		}
		else if (actor->status == Status::Healing)
		{
			HealthPoints += actor->HDAmount;
			if (HealthPoints >= 100)
			{
				HealthPoints =100;
			}
			
		}
		actor->DestroyOnOverlap();
	}
}