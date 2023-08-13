# Emeraude Engine

## Introduction

Emeraude is an open-source 3D world engine written in C++20. It uses Vulkan for the graphics, OpenAL for the sound and a home solution for scene management and physics. This project is educative. There is no final goal yet, except making a 3D environment to play with and to evolve from scratch with the algorithms linked to 3D scenery. This is the 6th form of the engine.

This project is written on Debian with QtCreator using CMake.

NOTE : Libraries and tools version are the used ones at time of writing (2022/03/11).

## Cross-platform tools

- CMake >= 3.21.0
- QtCreator >= 9.0.2 (Optional)
- CLion >= 2023.1 (Optional)
 
## Dependent Libraries

- Vulkan >= 1.2
- GLSLang >= 12.0.0
- OpenAL >= 1.19.1
- GLFW >= 3.3.8
- ASIO >= 1.22.1
- JsonCPP >= 1.9.5
- ZLIB >= 1.2.13
- JPEG >= 2.1.5
- PNG >= 1.6.39
- FreeType >= 2.12.1
- SNDFile >= 1.2.0
- SampleRate >= 0.2.2
- ALUT >= 1.1.0 (Optional)
- Taglib >= 1.13 (Optional)
- ImGUI >= 1.86 (Optional)
- GLM >= 0.9.9.8 (Optional)
- Eigen >= 3.4.0 (Optional)

NOTE : On Debian-like linux platform there is a script to install dependencies via APT automatically.

## Project configuration for Linux (Debian 12)

Steps are based on a Debian-like system. Normally, it can be reproduced with some modifications on others distros. 
Just skip the line 'setup-debian' for other system. Installs tools and dependencies manually.

### Platform-specific tools

- Ninja-build >= 1.11.1
- GCC >= 12 or Clang >= 14

### Setup for development

These command lines will ask for sudo password in order to install dev packages from official debian repository.

Feel free to open 'setup-debian' script before launching the command.

```bash
git clone --recurse-submodules git@bitbucket.org:londnoir/emeraude-engine.git
cd emeraude-engine
./setup-debian
./install
cd ..
```

## Project configuration for Windows

This project is intended to be compatible with Windows compilation through MinGW.
A compilation has been successfully done once, but nothing more since. 

## Project configuration for MacOS

This project is intended to be compatible with MacOSX compilation through Clang. 
But nothing has been tested or done yet.
