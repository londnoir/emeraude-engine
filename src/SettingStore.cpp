/*
 * Emeraude/SettingStore.cpp
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

#include "SettingStore.hpp"

namespace Emeraude
{
	void
	SettingStore::set (const std::string & name, const std::string & value) noexcept
	{
		m_variables[name] = value;
	}

	void
	SettingStore::setInArray (const std::string & name, const std::string & value) noexcept
	{
		auto arrayIt = m_arrays.find(name);

		if ( arrayIt == m_arrays.end() )
		{
			m_arrays[name] = {value};
		}
		else
		{
			arrayIt->second.emplace_back(value);
		}
	}

	bool
	SettingStore::variableExists (const std::string & name) const noexcept
	{
		return m_variables.find(name) != m_variables.cend();
	}

	bool
	SettingStore::arrayExists (const std::string & name) const noexcept
	{
		return m_arrays.find(name) != m_arrays.cend();
	}

	bool
	SettingStore::subStoreExists (const std::string & storeName) const noexcept
	{
		return m_subStores.find(storeName) != m_subStores.cend();
	}

	SettingStore &
	SettingStore::getSubStore (const std::string & storeName) noexcept
	{
		return m_subStores[storeName];
	}

	const SettingStore *
	SettingStore::getSubStorePointer (const std::string & storeName) const noexcept
	{
		auto storeIt = m_subStores.find(storeName);

		if ( storeIt != m_subStores.cend() )
		{
			return &(storeIt->second);
		}

		return nullptr;
	}

	SettingStore *
	SettingStore::getSubStorePointer (const std::string & storeName, bool createIfNotExists) noexcept
	{
		auto storeIt = m_subStores.find(storeName);

		if ( storeIt != m_subStores.end() )
		{
			return &(storeIt->second);
		}

		return createIfNotExists ? &(m_subStores[storeName]) : nullptr;
	}

	std::string
	SettingStore::get (const std::string & name) const noexcept
	{
		auto storeIt = m_variables.find(name);

		if ( storeIt != m_variables.cend() )
		{
			return storeIt->second;
		}

		return {};
	}

	std::string
	SettingStore::getOrSet (const std::string & name, const std::string & defaultValue) noexcept
	{
		auto storeIt = m_variables.find(name);

		if ( storeIt != m_variables.cend() )
		{
			return storeIt->second;
		}

		return m_variables[name] = defaultValue;
	}

	const std::vector< std::string > *
	SettingStore::getArray (const std::string & name) const noexcept
	{
		const auto storeIt = m_arrays.find(name);

		if ( storeIt == m_arrays.cend() )
		{
			return nullptr;
		}

		return &(storeIt->second);
	}

	std::vector< std::string > *
	SettingStore::getArray (const std::string & name) noexcept
	{
		auto storeIt = m_arrays.find(name);

		if ( storeIt == m_arrays.end() )
		{
			return nullptr;
		}

		return &(storeIt->second);
	}

	void
	SettingStore::clear () noexcept
	{
		this->clearData();

		this->clearSubStores();
	}

	void
	SettingStore::clearData () noexcept
	{
		m_variables.clear();
		m_arrays.clear();
	}

	void
	SettingStore::clearSubStores () noexcept
	{
		m_subStores.clear();
	}

	const std::map< std::string, std::string > &
	SettingStore::variables () const noexcept
	{
		return m_variables;
	}

	const std::map< std::string, std::vector< std::string > > &
	SettingStore::arrays () const noexcept
	{
		return m_arrays;
	}

	const std::map< std::string, SettingStore > &
	SettingStore::subStores () const noexcept
	{
		return m_subStores;
	}
}
