// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinActor.h"
#include "Components/SphereComponent.h"
#include "Glavni_lik.h"
#include "GameFramework/Character.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ACoinActor::ACoinActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ColliderComponent = CreateDefaultSubobject<USphereComponent>("ColliderComponent");
	SetRootComponent(ColliderComponent);
	ColliderComponent->SetGenerateOverlapEvents(true);
	ColliderComponent->SetHiddenInGame(false);
	ColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(
		this, &ACoinActor::OnBeginOverlapComponentEvent
	);
	

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(ColliderComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetGenerateOverlapEvents(false);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");
}

void ACoinActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void ACoinActor::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}
void ACoinActor::OnBeginOverlapComponentEvent(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
	)
{
	UE_LOG(LogTemp, Log, TEXT("Hello World"));
	AGlavni_lik* Char = Cast<AGlavni_lik>(OtherActor);
	if(!Char)	{return;}

	Char->AddCoin(1);
	
	Destroy();
}
