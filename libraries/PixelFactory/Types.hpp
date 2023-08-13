/*
 * Libraries/PixelFactory/Types.hpp
 * This file is part of Emeraude
 *
 * Copyright (C) 2012-2023 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude
 * 
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* C/C++ standard libraries. */
#include <cstddef>

/* Local inclusion for usages. */
#include "Path/File.hpp"

namespace Libraries::PixelFactory
{
	/** @brief Enumerate color channel mode. */
	enum class ChannelMode : size_t
	{
		Grayscale = 1UL,
		GrayscaleAlpha = 2UL,
		RGB = 3UL,
		RGBA = 4UL
	};

	/** @brief Enumerate color channel index. */
	enum class Channel : size_t
	{
		Red = 0UL,
		Green = 1UL,
		Blue = 2UL,
		Alpha = 3UL
	};

	/** @brief Enumerate type of compression for Pixmap file writing. */
	enum class Compression
	{
		None,
		LossLess,
		Destructive
	};

	/** @brief Enumerate filtering mode for enlarging or reducing an image. */
	enum class FilteringMode
	{
		Nearest,
		Linear,
		Cubic
	};

	/** @brief Enumerate drawing mode when copying image or a color onto an other. */
	enum class DrawPixelMode
	{
		Replace,
		Normal,
		Addition,
		Subtract,
		Multiply,
		Divide,
		Screen,
		Overlay,
		Difference,
		Darken,
		Lighten
	};

	/** @brief Enumerate grayscale conversion from RGB color. */
	enum class GrayscaleConversionMode
	{
		/* Gray = (Red + Green + Blue) / 3 */
		Average,
		/* Gray = 0.2989 * Red + 0.5866 * Green + 0.1145 * Blue */
		LumaRec601_1,
		/* Gray = 0.2126 * Red + 0.7152 * Green + 0.0722 * Blue */
		LumaRec709,
		/* Gray = 0.2220 * Red + 0.7067 * Green + 0.0713 * Blue */
		LumaITU,
		/* Gray = ( max(Red, Green, Blue) + min(Red, Green, Blue) ) / 2 */
		Desaturation,
		/* Gray = min(Red, Green, Blue) OR Gray = max(Red, Green, Blue) */
		Decomposition,
		/* Gray = Red OR Gray = Green OR ... */
		SingleChannel,
		ShadesScale
	};

	/** @brief Enumerate mirroring mode. */
	enum class MirrorMode
	{
		X,
		Y,
		Both
	};

	/** @brief  */
	enum class AlphaChannelPolicy
	{
		Add,
		Remove,
		Keep
	};

	/** @brief  */
	enum class Direction
	{
		Up,
		Down,
		Right,
		Left
	};

	static constexpr auto LuminanceRec6011Red = 0.2989F;
	static constexpr auto LuminanceRec6011Green = 0.5866F;
	static constexpr auto LuminanceRec6011Blue = 0.1145F;

	static constexpr auto LuminanceRec709Red = 0.2126F;
	static constexpr auto LuminanceRec709Green = 0.7152F;
	static constexpr auto LuminanceRec709Blue = 0.0722F;

	static constexpr auto LuminanceITURed = 0.2220F;
	static constexpr auto LuminanceITUGreen = 0.7067F;
	static constexpr auto LuminanceITUBlue = 0.0713F;
}
