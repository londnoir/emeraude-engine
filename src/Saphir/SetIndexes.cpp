/*
 * src/Saphir/SetIndexes.cpp
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

#include "SetIndexes.hpp"

/* STL inclusions. */
#include <limits>
#include <algorithm>
#include <sstream>

namespace Emeraude::Saphir
{
	void
	SetIndexes::enableSet (SetType setType) noexcept
	{
		if ( this->isSetEnabled(setType) )
		{
			return;
		}

		m_setTypes.emplace_back(setType);
	}

	bool
	SetIndexes::isSetEnabled (SetType setType) const noexcept
	{
		return std::ranges::any_of(m_setTypes, [setType] (const auto & currentDescriptorSetType) {
			return currentDescriptorSetType == setType;
		});
	}

	uint32_t
	SetIndexes::set (SetType setType) const noexcept
	{
		const auto limit = static_cast< uint32_t >(m_setTypes.size());

		for ( uint32_t index = 0; index < limit; index++ )
		{
			if ( m_setTypes[index] == setType )
			{
				return index;
			}
		}

		return std::numeric_limits< uint32_t >::max();
	}

	std::ostream &
	operator<< (std::ostream & out, const SetIndexes & obj)
	{
		return out << SetIndexes::ClassId << " data :" "\n"
			"Set per view : " << obj.set(SetType::PerView) << "\n"
			"Set per light : " << obj.set(SetType::PerLight) << "\n"
			"Set per model layer : " << obj.set(SetType::PerModelLayer) << "\n";
	}

	std::string
	to_string (const SetIndexes & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
