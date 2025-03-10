/*
 * src/SettingStore.cpp
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

#include "SettingStore.hpp"

namespace Emeraude
{
	void
	SettingStore::setVariableInArray (const std::string & name, const std::any & value) noexcept
	{
		const auto arrayIt = m_arrays.find(name);

		if ( arrayIt == m_arrays.end() )
		{
			m_arrays[name] = {value};
		}
		else
		{
			arrayIt->second.emplace_back(value);
		}
	}

	const SettingStore *
	SettingStore::getSubStorePointer (const std::string & storeName) const noexcept
	{
		const auto storeIt = m_subStores.find(storeName);

		if ( storeIt == m_subStores.cend() )
		{
			return nullptr;
		}

		return &(storeIt->second);
	}

	SettingStore *
	SettingStore::getSubStorePointer (const std::string & storeName, bool createIfNotExists) noexcept
	{
		const auto storeIt = m_subStores.find(storeName);

		if ( storeIt != m_subStores.end() )
		{
			return &(storeIt->second);
		}

		return createIfNotExists ? &(m_subStores[storeName]) : nullptr;
	}

	const std::any *
	SettingStore::getValuePointer (const std::string & name) const noexcept
	{
		const auto storeIt = m_variables.find(name);

		if ( storeIt == m_variables.cend() )
		{
			return nullptr;
		}

		return &(storeIt->second);
	}

	const std::any *
	SettingStore::getValuePointerOrSet (const std::string & name, const std::string & defaultValue) noexcept
	{
		const auto storeIt = m_variables.find(name);

		if ( storeIt == m_variables.cend() )
		{
			return &(m_variables.emplace(name, defaultValue).first->second);
		}

		return &(storeIt->second);
	}

	const std::vector< std::any > *
	SettingStore::getArrayPointer (const std::string & name) const noexcept
	{
		const auto storeIt = m_arrays.find(name);

		if ( storeIt == m_arrays.cend() )
		{
			return nullptr;
		}

		return &(storeIt->second);
	}

	std::vector< std::any > *
	SettingStore::getArrayPointer (const std::string & name) noexcept
	{
		const auto storeIt = m_arrays.find(name);

		if ( storeIt == m_arrays.end() )
		{
			return nullptr;
		}

		return &(storeIt->second);
	}
}
