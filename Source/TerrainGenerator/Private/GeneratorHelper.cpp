// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorHelper.h"

// Sets default values for this component's properties
UGeneratorHelper::UGeneratorHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGeneratorHelper::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGeneratorHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UGeneratorHelper::Remap(float value, float low1, float high1, float low2, float high2)
{
	return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}

float UGeneratorHelper::GetHeight(float height, float g, float top, float bottom)
{
	float desertFlatten = 0.01f;
	float gorySharpen = 8;

	height *= FMath::Lerp(desertFlatten, gorySharpen, FMath::Pow(g,2));

	float scaledHeightMap = (((top - bottom) * (height + 1)) / 2) + bottom;

	return scaledHeightMap;
}



void UGeneratorHelper::GenerateMeshArrays(const int plateSize, const int mapSize, const int seed, const int biomeSeed, const int waterSeed, const float top, const float bottom, const float flatten, const float sharpen, const float frequency, const float biomeFrequency, const float persistence, const int octaves, const float waterLevel, int waterMeshDivision, const int offsetX, const int offsetY, const float objFrequency, const int objNum, const bool generateRivers, const float waterFrequency, TArray<FVector>& verts, TArray<int>& tris, TArray<FVector2D>& uvs, TArray<FLinearColor>& vertColors, TArray<FVector>& vertsWater, TArray<int>& trisWater, TArray<FVector2D>& uvsWater, TArray<FLinearColor>& vertWaterColors, TArray<FVector>& objPosition, TArray<int>& objType)
{
	const siv::PerlinNoise::seed_type see = seed;
	const siv::PerlinNoise perlin{ see };

	const siv::PerlinNoise::seed_type see2 = biomeSeed;
	const siv::PerlinNoise perlin2{ see2 };

	const siv::PerlinNoise::seed_type see3 = waterSeed;
	const siv::PerlinNoise perlin3{ see3 }; 

	if (waterMeshDivision <= 0) waterMeshDivision = 1;

	float uvSpace = 50.f / FMath::Max(mapSize, mapSize);
	int v = 0, vw = 0;
	float vertexOffset = plateSize * 0.5f;
	for (int32 x = 0; x <= mapSize; x++)
	{
		for (int32 y = 0; y <= mapSize; y++)
		{
			float vheight = perlin.octave2D_01((x+offsetX) * frequency, (y+offsetY) * frequency, octaves, persistence);
			vheight = Remap(vheight, 0, 1, 0.3, 1);

			if (generateRivers) {
				float waterPass = perlin3.octave2D_01((x + offsetX) * waterFrequency, (y + offsetY) * waterFrequency, octaves, persistence);
				if (waterPass > 0.5) waterPass = 1 - waterPass;
				if (waterPass >= 0.4) {
					vheight *= Remap(waterPass, 0.5, 0.4, 0.1, 1);
				}
			}

			vertColors.Add(FLinearColor(vheight, perlin2.octave2D_01((x + offsetX) * biomeFrequency, (y + offsetY) * biomeFrequency, octaves, persistence), 0, 1)); // R = wysokosc | G = biome | B = | A = 

			float height = GetHeight(vheight, vertColors.Last().G, top, bottom);
			if (height < (top + bottom) / 2.0f) height = ((top + bottom) / 2.0f);
			verts.Add(FVector((x * plateSize) - vertexOffset, (y * plateSize) - vertexOffset, FMath::Pow(height * sharpen, flatten)));
			uvs.Add(FVector2D(x * uvSpace, y * uvSpace));

			if (x % waterMeshDivision == 0 && y % waterMeshDivision == 0) {
				float waterHeight = GetHeight(waterLevel, vertColors.Last().G, top, bottom);
				if (waterHeight < (top + bottom) / 2.0f) waterHeight = ((top + bottom) / 2.0f);
				vertsWater.Add(FVector((x * plateSize) - vertexOffset, (y * plateSize) - vertexOffset, FMath::Pow(waterHeight * sharpen, flatten)));
				vertWaterColors.Add(FLinearColor(vheight, 0 , 0, 1)); // R = wysokosc | G = | B = | A = 
				uvsWater.Add(FVector2D(x * uvSpace, y * uvSpace));
				if (y < mapSize && x < mapSize) {
					trisWater.Add(vw);
					trisWater.Add(vw + 1);
					trisWater.Add(vw + (mapSize/ waterMeshDivision + 1));

					trisWater.Add(vw + (mapSize/ waterMeshDivision + 1));
					trisWater.Add(vw + 1);
					trisWater.Add(vw + (mapSize/ waterMeshDivision + 1) + 1);
					vw++;
				}
			}
			if (y < mapSize && x < mapSize ) {
				tris.Add(v);
				tris.Add(v + 1);
				tris.Add(v + (mapSize + 1));

				tris.Add(v + (mapSize + 1));
				tris.Add(v + 1);
				tris.Add(v + (mapSize + 1) + 1);

				v++;
			}

			if (!biomeElementsInfo.IsEmpty()) {
				float G = vertColors.Last().G;
				for (size_t i = 0; i < biomeElementsInfo.Num(); i++) {
					if (vheight < biomeElementsInfo[i].heightMax && vheight > biomeElementsInfo[i].heightMin && G < biomeElementsInfo[i].biomeMax && G > biomeElementsInfo[i].biomeMin) {
						float fade = 1;
						if(G > biomeElementsInfo[i].biomeMax - biomeElementsInfo[i].fade)fade = Remap(G, biomeElementsInfo[i].biomeMax-biomeElementsInfo[i].fade, biomeElementsInfo[i].biomeMax, 1, 0);
						else if (G < biomeElementsInfo[i].biomeMin + biomeElementsInfo[i].fade)fade = Remap(G, biomeElementsInfo[i].biomeMin, biomeElementsInfo[i].biomeMin + biomeElementsInfo[i].fade, 1, 0);
						if (rand() % biomeElementsInfo[i].frequency < objFrequency / fade) {
							objPosition.Add(verts.Last());
							objType.Add(biomeElementsInfo[i].types[rand()% biomeElementsInfo[i].types.Num()]);
						}
					}
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("biomesElementInfo EMPTY !"));
			}

		}
		if (x < mapSize) {
			v++;
			if (x % waterMeshDivision == 0) {
				vw++;
			}
		}
	}
}

