// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.generated.h"


UCLASS()
class T3_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent * CameraSpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Health")
	float HealthPoints=100;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
    TSubclassOf<UUserWidget> PLayerWidgetClass;

	UUserWidget* PlayerHealth;

	bool IsDead = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Turn(float Amount);
	void LookUp(float Amount);
	void MoveForward(float Value);
	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void RestartGame();

};
