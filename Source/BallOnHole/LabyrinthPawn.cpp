// Fill out your copyright notice in the Description page of Project Settings.


#include "LabyrinthPawn.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TimerManager.h"

// Sets default values
ALabyrinthPawn::ALabyrinthPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Meshes
	pivot_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pivot only"));
	pivot_->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	walls_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Walls Mesh Comp"));	
	walls_->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	floor_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor Mesh Comp"));
	floor_->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	// Pivot
	RootComponent = pivot_;
	//floor_->SetupAttachment(StaticCast<USceneComponent*>(walls_));
	floor_->SetupAttachment(RootComponent);
	walls_->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALabyrinthPawn::BeginPlay()
{
	Super::BeginPlay();
	controller_ = GetWorld()->GetFirstPlayerController();
	controller_->bShowMouseCursor = false;
	controller_->bEnableClickEvents = true;
	controller_->bEnableMouseOverEvents = true;
	controller_->GetMousePosition(last_mouse_pos_.X, last_mouse_pos_.Y);
	FTimerHandle time;
	GetWorldTimerManager().SetTimer(time, this, &ALabyrinthPawn::startGame, 3.f);
}

// Called every frame
void ALabyrinthPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	auto rot = GetRotationVelocityXY(DeltaTime);
	if (start_) {		
		pivot_->SetWorldRotation(FRotator(FMath::Clamp<float>(GetActorRotation().Pitch - rot.X, -10.f, 10.f),
			0.f,
			FMath::Clamp<float>(GetActorRotation().Roll + rot.Y, -10.f, 10.f)));
	}
}

FVector2D ALabyrinthPawn::GetRotationVelocityXY(float& deltaTime)
{
	controller_->GetMousePosition(current_mouse_pos_.X, current_mouse_pos_.Y);
	FVector2D delta_mouse = current_mouse_pos_ - last_mouse_pos_;
	delta_mouse.X = FMath::Clamp<float>(delta_mouse.X, -20.f, 20.f);
	delta_mouse.Y = FMath::Clamp<float>(delta_mouse.Y, -20.f, 20.f);
	FVector2D velocity = delta_mouse / (1200.f * deltaTime);
	controller_->GetMousePosition(last_mouse_pos_.X, last_mouse_pos_.Y);
	//UE_LOG(LogTemp, Warning, TEXT("vel X: %f   -   vel Y: %f"), velocity.X, velocity.Y);
	return velocity;
}

void ALabyrinthPawn::startGame()
{
	start_ = true;
}

// Called to bind functionality to input
void ALabyrinthPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

