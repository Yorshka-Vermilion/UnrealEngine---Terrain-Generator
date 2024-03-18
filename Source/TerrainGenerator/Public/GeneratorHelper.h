// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <random>
#include "PerlinNoise.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GeneratorHelper.generated.h"

USTRUCT(BlueprintType)
struct FBiomeElementsInfo
{
    GENERATED_BODY()


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biomes")
		TArray<int32> types;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biomes")
		float biomeMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biomes")
		float biomeMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biomes")
		float heightMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biomes")
		float heightMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biomes")
		float fade;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biomes")
		int frequency;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LAB1_API UGeneratorHelper : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGeneratorHelper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float Remap(float value, float low1, float high1, float low2, float high2);
	float GetHeight(float height, float g, float top, float bottom);

	UFUNCTION(BlueprintCallable)
		void GenerateMeshArrays(const int plateSize, const int mapSize, const int seed, const int biomeSeed, const int waterSeed, const float top, const float bottom, const float flatten, const float sharpen, const float frequency, const float biomeFrequency, const float persistence, const int octaves, const float waterLevel, int waterMeshDivision, const int offsetX, const int offsetY, const float objFrequency, const int objNum, const bool generateRivers, const float waterFrequency, TArray<FVector>& verts, TArray<int>& tris, TArray<FVector2D>& uvs, TArray<FLinearColor>& vertColors, TArray<FVector>& vertsWater, TArray<int>& trisWater, TArray<FVector2D>& uvsWater, TArray<FLinearColor>& vertWaterColors, TArray<FVector>& objPosition, TArray<int>& objType);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biomes")
		TArray<FBiomeElementsInfo> biomeElementsInfo;
};

