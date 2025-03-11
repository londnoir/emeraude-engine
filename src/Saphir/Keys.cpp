/*
 * src/Saphir/Keys.cpp
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

#include "Keys.hpp"

/* STL inclusions. */
#include <sstream>
#include <string>

namespace EmEn::Saphir
{
	std::string
	MatrixPC (const char * componentName) noexcept
	{
		return (std::stringstream{} << Keys::PushConstant::Matrices << '.' << componentName).str();
	}

	std::string
	OverlayPC (const char * componentName) noexcept
	{
		return (std::stringstream{} << Keys::PushConstant::Overlay << '.' << componentName).str();
	}

	std::string
	ViewUB (const char * componentName) noexcept
	{
		return (std::stringstream{} << Keys::UniformBlock::View << '.' << componentName).str();
	}

	std::string
	CubeViewUB (const char * memberName, const char * indexVariableName, const char * componentName) noexcept
	{
		return (std::stringstream{} << Keys::UniformBlock::View << '.' << memberName << '[' << indexVariableName << ']' << '.' << componentName).str();
	}

	std::string
	MaterialUB (const char * componentName) noexcept
	{
		return (std::stringstream{} << Keys::UniformBlock::Material << '.' << componentName).str();
	}

	std::string
	LightUB (const char * componentName) noexcept
	{
		return (std::stringstream{} << Keys::UniformBlock::Light << '.' << componentName).str();
	}
}
