# Emeraude Engine (LGPLv3)

This project is a cross-platform engine to render a scene in 3D using the Vulkan API and written in C++20. There is an audio layer and a minimal physics simulation layer.

This lib provide :
- a scene manager based on a node system.
- a resources manager to load data hierarchically.
- a material manager with auto-generated shaders
- an overlay manager to draw on screen.
- ...

The name comes from a DOS game called "The Legend of Kyrandia" which makes extensive use of gemstones. As a child, I was a fan of emeralds.

# External dependencies

The engine needs some external libraries, most of them are provided by an external repository that creates an archive of static binaries (https://github.com/londnoir/ext-deps-generator).
Others are submodules and compiled directly with the final binary.

# Requirements

 - A compiler compatible with C++20
 - CMake (3.25.1) to generate the project
 - Python3
 - Vulkan SDK from https://vulkan.lunarg.com/sdk/home

This library is maintained from Debian 12 (stable) using G++ 12.2.
On macOS, you need Xcode environment installed for the minimal SDK 12.
On Windows, you need the "Visual Studio 2022" environment installed.

Note: Further information will come here to complete dependent pieces of software and libraries installation. 
But this shouldn't be complicated to resolve problems described by CMake logs.

# Quick compilation from the terminal

For now, you need to manually copy the results of "ext-deps-generator" into the directory "emeraude-engine/dependencies/" to CMake find the static libraries.
Keep the exact directory name (linux|mac|windows).(x86_64|arm64)-(Debug|Release).

This will produce the shared library.

## Release

```bash
git clone --recurse-submodules https://github.com/londnoir/emeraude-engine.git
cmake -S ./emeraude-engine -B ./emeraude-engine/cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build ./emeraude-engine/cmake-build-release --config Release
```

## Debug

```bash
git clone --recurse-submodules https://github.com/londnoir/emeraude-engine.git
cmake -S ./emeraude-engine -B ./emeraude-engine/cmake-build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build ./emeraude-engine/cmake-build-debug --config Debug
```
