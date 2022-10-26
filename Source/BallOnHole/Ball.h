// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UStaticMeshComponent;
class USphereComponent;
UCLASS()
class BALLONHOLE_API ABall : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ball_mesh_;
		USphereComponent* sphere_component_;
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
