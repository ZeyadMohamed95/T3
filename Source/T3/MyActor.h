// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UENUM()
enum Status
{
	Healing     UMETA(DisplayName = "Healing"),
	Damage      UMETA(DisplayName = "Damage"),
};
UCLASS()
class T3_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	TEnumAsByte<Status> status;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")	
	class UCapsuleComponent* TriggerCapsule;

	UPROPERTY(EditAnywhere, Category = "Healing/Damage")
	float HDAmount = 20;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void DestroyOnOverlap();
	
};
