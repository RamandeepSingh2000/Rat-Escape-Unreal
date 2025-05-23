// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Weapon.h"
#include "Character/Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
	ProjectileSpawnPoint->SetRelativeLocation(FVector(100, 0, 0));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon::Fire()
{
	if (ProjectileClass == nullptr)
		return;

	UWorld* World = GetWorld();
	if (World == nullptr)
		return;

	FVector MuzzleLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator MuzzleRotation = ProjectileSpawnPoint->GetComponentRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	AProjectile* ProjectileInstance = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	if (ProjectileInstance != nullptr)
		ProjectileInstance->FireInDirection(ProjectileSpawnPoint->GetForwardVector());

	if (SoundEffect != nullptr)
		UGameplayStatics::PlaySound2D(GetWorld(), SoundEffect);
}

