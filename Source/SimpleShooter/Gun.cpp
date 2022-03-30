// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	//SetRootComponent(Root);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash , SkeletalMesh , TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound , SkeletalMesh , TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;

	bool bSuccess = GunTrace(Hit , ShotDirection);

	if(bSuccess){
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld() , ImpactEffect , Hit.Location , ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld() , ImpactSound , Hit.Location );
		
		AActor* HitActor = Hit.GetActor();
		if(HitActor){
			FPointDamageEvent DamageEvent(Damage , Hit ,ShotDirection , nullptr);
			AController* OwnerController = GetController(); 
			HitActor->TakeDamage(Damage , DamageEvent , OwnerController ,this);
		}
	}
		

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::GunTrace(FHitResult &Hit , FVector& ShotDirection)
{
	AController* OwnerController = GetController();
	if(OwnerController){
		FVector Location;
		FRotator Rotation;
		OwnerController->GetPlayerViewPoint(Location , Rotation);
		//DrawDebugCamera(GetWorld() , Location , Rotation , 90 , 2.0 , FColor::Red , true);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

		ShotDirection = -Rotation.Vector();
		
		FVector End = Location + Rotation.Vector() * FireRange;
		return GetWorld()->LineTraceSingleByChannel(Hit , Location , End , ECollisionChannel::ECC_GameTraceChannel1 , Params);
	}
	return false;
}

AController* AGun::GetController() const
{
	APawn* OwningActor = Cast<APawn>(GetOwner());
	if(OwningActor)
		return OwningActor->GetController();
	return nullptr;
}

