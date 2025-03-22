# Development history log

## Alpha version 0.7 (C++20, ~2023)

This is the version that is mostly equal to the OpenGL version.
New features, new technics and adoption of C++20.

## Alpha version 0.6 [NON-EXISTENT] (C++17, ~2021)

This is a transitional version started in 2020 to rewrite the graphics engine for using Vulkan instead of OpenGL and the first version to draw the minimal on the screen.
This change was a significant decision and a huge step backward in development with many feature losses.
It was deliberate to drop OpenGL support instead of adding a new rendering backend to take full advantage of Vulkan's benefits with multithreading.
From this version, the idea was to recover everything that had been done with the OpenGL version.

## Alpha version 0.5 [ARCHIVED] (C++14, ~2019)

This is a minor rewrite of the engine itself.
The idea behind this change was to better use large project management tools like git, cmake, external libraries.
This is the latest archived version and the very last version of the engine that uses OpenGL.

## Alpha version 0.4 [ARCHIVED] (C++11, ~2015)

This is the third complete rewrite of the engine in C++, it's mainly a new empty structure from scratch and then retaining what was good from the previous version.
By learning advanced techniques in C++ and OOP, it leads to a new way of thinking about the engine structure.
This version will be the last where the entire code structure will be reworked.

## Alpha version 0.3 [ARCHIVED] (C++11, ~2013)

This is the second attempt to rewrite the engine in C++ from zero.
Learning C++ is difficult and leads to bad decisions... Alpha 2 was a big failure!

## Alpha version 0.2 [ARCHIVED] (C++03/C++0x, ~2012)

This is the first complete rewrite of the engine but using C++.
C++ provides a better way to express abstract concepts for an engine and is the first attempt at engine standardization.

## Alpha version 0.1 [ARCHIVED] (C, ~2010)

This is the first try to create an engine with OpenGL using C.
The idea was mainly to automatize OpenGL rendering with a scene with a sky, a ground and entities.
