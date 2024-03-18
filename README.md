# UnrealEngine---Terrain-Generator
Dynamic, real-time terrain generator for Unreal Engine. It uses both, C++ and Blueprint system to make it user-friendly with C++ flexibility. Generated map is splitted into chunks, which are unloaded if player gets too far from chunk (like in Minecraft). Once generated chunk stays generated, when player enters same area again, chunks are loaded from the memory, they are only generated on the first pass.

# Preview

### Wiremesh

### Real-time

### Screens

![obraz](https://github.com/Yorshka-Vermilion/UnrealEngine---Terrain-Generator/assets/59543577/4495deaa-ebd4-4993-af4b-16cdcb15e57b)
![obraz](https://github.com/Yorshka-Vermilion/UnrealEngine---Terrain-Generator/assets/59543577/b41fbd1d-47da-45ca-a2c6-48a466fde466)
![obraz](https://github.com/Yorshka-Vermilion/UnrealEngine---Terrain-Generator/assets/59543577/4d67ebec-9821-4236-b8b9-4d14d7eb9392)

# Usage:

Drag and drop "ProceduralGeneratorMain" to the world, thats all.

# Customization:

By going into "ProceduralGenerator" blueprint you can access following options:

![Przechwytywanie](https://github.com/Yorshka-Vermilion/UnrealEngine---Terrain-Generator/assets/59543577/bb3bdcb4-0a28-4b46-b3ff-47ebfcc297a4)


- **Water Mesh Size** - size of a water "tile", smaller ones have higher resolution, while begin slower to generate.
- **Meshes** - array of static meshes that will appear in the world. You can put whatever you want here.
- **Gen X** and **Gen Y** - for offseting generator by a value.
- **Biome Elements Info** - this is array of biomes.
  - **Types** - list for meshes which can appear on this biome.
  - **Biome Max** and **Biome Min** - you specify range of values (0-1) in which generator (randomly) will generate your biome. If you overlap some biomes in this setting, you will have gradient effect on terrain on biome borders.
  - **Height Max** and **Height Min** - for specify range of height on which biome can appear. For example if you don't want desert to appear on mountain tops, then you should put **Height Max** to low value.
  - **Fade** - this value specify how long will it take one biome to become another. 0 fade, means if two biomes touch the translation is sharp, fade above 0 will generate some gradient between biomes.
  - **Frequency** - frequency of given biome.
  - ![Przechwytywanie](https://github.com/Yorshka-Vermilion/UnrealEngine---Terrain-Generator/assets/59543577/8bf55b7c-c3a9-498e-8ee4-63ee88bc7cf0)
- **Water Frequency** - frequency of a water. (water is generated on heights below 0).
- **Generate Rivers** - if checked, generator will generate continous rivers instead of lakes.
- **Obj Frequency** - global frequency of objects generation
- **Water Mesh Division** - how divided water mesh should be. Higher values means more triangles for water tiles.
- **Octaves, Persistence, Frequency, Sharpen, Flatten** - values for perlin noise.
- **Biome Frequency** - specify how big biomes should be, lower values means bigger biomes
- **Bottom, Top** - minimal and maximal height on which terrain can be generated
- **Water Seed, Biome Seed, Seed** - seeds for water, biomes, and everything else.

# Disclaimer

For meshes, i've been using DreamscapeSeries meshes from Epic Store.
