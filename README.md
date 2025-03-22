# Emeraude Engine (LGPLv3)

This project is a cross-platform engine to render a scene in 3D using the Vulkan API and written in C++20. There is an audio layer and a minimal physics simulation layer.

This lib provide :
- a scene manager based on a node system.
- a resources manager to load data in a hierarchical manner.
- a material manager with auto generated shaders
- an overlay manager to draw on screen.
- ...

# External dependencies

The engine need some external libraries, most of them are provided by an external repository that creates an archive of static binaries (https://github.com/londnoir/ext-deps-generator).
Others are submodules and compiled directly with the final binary.

# Requirements

 - A compiler compatible with C++20
 - CMake (3.25.1) to generate the project
 - Python3
 - Vulkan SDK from https://vulkan.lunarg.com/sdk/home

This library is maintained from Debian 12 (stable) using G++ 12.2.
On macOS, you need Xcode environment installed for the minimal SDK 12.
On Windows, you need Visual Studio 2022 environment installed.

Note: Further information will come here to complete dependent softwares and libraries installation. 
But, this shouldn't be complicated to resolve problems described by CMake logs.

# Quick compilation from a terminal

For now, you need to copy manually the results of "ext-deps-generator" into the directory "emeraude-engine/dependencies/" in order to CMake find the static libraries.
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

## Rules of development

1. Readability. The code should be easily readable by a 5-year experienced C++ programmer. It makes extensive use of OOP, templates and metaprogramming.
2. Performance. Once readability is achieved, the goal is performance. The final program should make the best use of the CPU, RAM, and GPU for what they were designed for.
3. Maintainability. Finally, the code should be as easily modifiable as possible. It strives to be compartmentalized and organized by functionality and concept.
