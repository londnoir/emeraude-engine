/*
 * Emeraude/Graphics/Renderable/AbstractSeaLevel.cpp
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

#include "AbstractSeaLevel.hpp"

namespace Emeraude::Graphics::Renderable
{
	AbstractSeaLevel::AbstractSeaLevel (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	void
	AbstractSeaLevel::setReadyForInstanciation (bool state) noexcept
	{
		if ( state )
			this->enableFlag(IsReadyForInstanciation);
		else
			this->disableFlag(IsReadyForInstanciation);
	}

	bool
	AbstractSeaLevel::isReadyForInstantiation () const noexcept
	{
		return this->isFlagEnabled(IsReadyForInstanciation);
	}

	int
	AbstractSeaLevel::flags (size_t) const noexcept
	{
		return m_renderableFlags;
	}
}
