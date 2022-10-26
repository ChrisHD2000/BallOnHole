// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LabyrinthPawn.generated.h"
class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class BALLONHOLE_API ALabyrinthPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALabyrinthPawn();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* walls_;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* floor_;
/*	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* camera_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* spring_arm_;*/
protected:
	APlayerController* controller_;
	UStaticMeshComponent* pivot_;
	bool start_ = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector2D GetRotationVelocityXY(float &deltaTime);
	FVector2D last_mouse_pos_ , current_mouse_pos_;
	void startGame();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
