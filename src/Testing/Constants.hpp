/*
 * src/Testing/Constants.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

#ifdef DEBUG
	#define RES_BASE_PATH "./"
#else
	#define RES_BASE_PATH "./"
#endif

/* NOTE: Source images. */
static const std::filesystem::path FixedFont{RES_BASE_PATH "/test-assets/fixed-font.tga"};
static const std::filesystem::path TrueTypeFont{RES_BASE_PATH "/test-assets/Joystick.Bold.ttf"};
static const std::filesystem::path LargeRGB{RES_BASE_PATH "/test-assets/1200x800-RBG.jpg"};
static const std::filesystem::path ExtraLargeRGB{RES_BASE_PATH "/test-assets/8160x6144-RBG.jpg"};
static const std::filesystem::path MediumGrayscale{RES_BASE_PATH "/test-assets/512x512-Grayscale.png"};
static const std::filesystem::path MediumGrayscaleAlpha{RES_BASE_PATH "/test-assets/512x512-GrayscaleAlpha.png"};
static const std::filesystem::path MediumPalette{RES_BASE_PATH "/test-assets/512x512-Palette.png"};
static const std::filesystem::path MediumRGB{RES_BASE_PATH "/test-assets/512x512-RGB.png"};
static const std::filesystem::path MediumRGBA{RES_BASE_PATH "/test-assets/512x512-RGBA.png"};
static const std::filesystem::path SmallPatternRBG_1{RES_BASE_PATH "/test-assets/126x126-RGB_pattern001.png"};
static const std::filesystem::path SmallPatternRBG_2{RES_BASE_PATH "/test-assets/126x126-RGB_pattern002.png"};
static const std::filesystem::path SmallPatternRBG_3{RES_BASE_PATH "/test-assets/126x126-RGB_pattern003.png"};
static const std::filesystem::path MediumPatternRBG_1{RES_BASE_PATH "/test-assets/256x256-RGB_pattern001.png"};
static const std::filesystem::path SmallRGBA{RES_BASE_PATH "/test-assets/64x64-RGBA.png"};
