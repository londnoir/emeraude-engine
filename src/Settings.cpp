/*
 * Emeraude/Settings.cpp
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

#include "Settings.hpp"

/* C/C++ standard libraries. */
#include <fstream>
#include <iostream>
#include <stack>

/* Local inclusions */
#include "Arguments.hpp"
#include "Tracer.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/json.hpp"

namespace Emeraude
{
	using namespace Libraries;

	const size_t Settings::ClassUID{Observable::getClassUID()};
	std::array< Settings *, 2 > Settings::s_instances{nullptr, nullptr}; // NOLINT NOTE: Singleton behavior

	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay, cppcoreguidelines-pro-bounds-constant-array-index)
	Settings::Settings (const Arguments & arguments, SettingsType type, const char * serviceInstanceName) noexcept
		: ServiceInterface(serviceInstanceName), m_arguments(arguments), m_type(type)
	{
		const auto key = static_cast< size_t >(m_type);

		if ( s_instances[key] != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n";

			std::terminate();
		}

		s_instances[key] = this;

	}

	Settings::~Settings ()
	{
		for ( auto & pointer : s_instances )
		{
			if ( pointer == this )
			{
				pointer = nullptr;

				break;
			}
		}

		const auto key = static_cast< size_t >(m_type);

		s_instances[key] = nullptr;
	}

	Settings *
	Settings::instance (SettingsType type) noexcept
	{
		const auto key = static_cast< size_t >(type);

		return s_instances[key];
	}
	// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay, cppcoreguidelines-pro-bounds-constant-array-index)

	bool
	Settings::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Settings::usable () const noexcept
	{
		return !m_filepath.empty();
	}

	bool
	Settings::readLevel (const Json::Value & data, SettingStore & store) noexcept // NOLINT(misc-no-recursion)
	{
		for ( const auto & name : data.getMemberNames() )
		{
			const auto & items = data[name];

			if ( items.isObject() )
			{
				auto & subStore = store.getSubStore(name);

				if ( !this->readLevel(items, subStore) )
				{
					return false;
				}
			}
			else if ( items.isArray() )
			{
				for ( const auto & item : items )
				{
					store.setInArray(name, item.asString());
				}
			}
			else
			{
				store.set(name, items.asString());
			}
		}

		return true;
	}

	bool
	Settings::readFile (const Path::File & filepath) noexcept
	{
		const Json::CharReaderBuilder builder{};

		std::ifstream json{to_string(filepath), std::ifstream::binary};

		if ( !json.is_open() )
		{
			TraceError{ClassId} << "Unable to read the file " << filepath << "!";

			return false;
		}

		Json::Value root{};

		std::string errors{};

		if ( !Json::parseFromStream(builder, json, &root, &errors) )
		{
			TraceError{ClassId} <<
				"Unable to parse JSON file ! "
				"Errors :\n" << errors;

			return false;
		}

		return this->readLevel(root, m_store);
	}

	bool
	Settings::writeLevel (const SettingStore & store, Json::Value & data) const noexcept // NOLINT(misc-no-recursion)
	{
		/* Writes sub store to this level. */
		for ( const auto & subStore : store.subStores() )
		{
			auto & json = data[subStore.first];

			if ( !this->writeLevel(subStore.second, json) )
			{
				return false;
			}
		}

		/* Write variables to this level. */
		for ( const auto & variable : store.variables() )
		{
			data[variable.first] = variable.second;
		}

		/* Write array to this level. */
		for ( const auto & array : store.arrays() )
		{
			data[array.first] = Json::arrayValue;

			for ( const auto & variable : array.second )
			{
				data[array.first].append(variable);
			}
		}

		return true;
	}

	bool
	Settings::writeFile (const Path::File & filepath) const noexcept
	{
		Json::Value root{};

		/* 1. JSON File header */
		{
			const auto timestamp = time(nullptr);
			const auto * now = localtime(&timestamp); // NOLINT(concurrency-mt-unsafe) NOTE: Called once !

			root[VersionKey] = (std::stringstream{} << ENGINE_VERSION_MAJOR << '.' << ENGINE_VERSION_MINOR << '.' << ENGINE_VERSION_PATCH).str();
			root[DateKey] = (std::stringstream{} << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday).str(); // NOLINT(*-magic-numbers)
		}

		/* 2. JSON File body */
		{
			if ( !this->writeLevel(m_store, root) )
			{
				Tracer::error(ClassId, "Unable to generate a store JSON data.");

				return false;
			}
		}

		/* 3. File writing */
		{
			Json::StreamWriterBuilder writer{};
			writer["indentation"] = "\t";
			writer["dropNullPlaceholders"] = true;

			const auto jsonString = Json::writeString(writer, root);

			if ( jsonString.empty() )
			{
				TraceError{ClassId} << "Unable to get JSON string from writer ! (JsonCpp library error)";

				return false;
			}

			return Utility::filePutContents(filepath, jsonString);
		}
	}

	SettingStore *
	Settings::getStorePointer (const std::string & key, std::string & variableName) noexcept
	{
		/* We execute in the root store. */
		auto * currentStorePtr = &m_store;

		if ( key.find('/') != std::string::npos )
		{
			auto list = String::explode(key, '/', false);

			/* Send the variable name outside the function. */
			variableName = list.back();

			/* The last part is the variable. */
			list.pop_back();

			for ( const auto & term : list )
			{
				currentStorePtr = currentStorePtr->getSubStorePointer(term, true);
			}
		}
		else
		{
			variableName = key;
		}

		return currentStorePtr;
	}

	const SettingStore *
	Settings::getStorePointer (const std::string & key, std::string & variableName) const noexcept
	{
		/* We execute in the root store. */
		const auto * currentStorePtr = &m_store;

		if ( key.find('/') != std::string::npos )
		{
			auto list = String::explode(key, '/', false);

			/* Send the variable name outside the function. */
			variableName = list.back();

			/* The last part is the variable. */
			list.pop_back();

			for ( const auto & term : list )
			{
				currentStorePtr = currentStorePtr->getSubStorePointer(term);
			}
		}

		return currentStorePtr;
	}

	void
	Settings::setFilepath (const Path::File & filepath) noexcept
	{
		m_filepath = filepath;
	}

	void
	Settings::doNotCreateConfigFile () noexcept
	{
		TraceWarning{ClassId} << "Automatic writing '" << m_filepath << "' settings file is disabled.";

		m_flags[SaveAtExit] = false;
	}

	bool
	Settings::variableExists (const std::string & key) const noexcept
	{
		std::string variableName{};

		const auto * storePtr = this->getStorePointer(key, variableName);

		if ( storePtr == nullptr )
		{
			return false;
		}

		return storePtr->variableExists(variableName);
	}

	bool
	Settings::arrayExists (const std::string & key) const noexcept
	{
		std::string variableName{};

		const auto * storePtr = this->getStorePointer(key, variableName);

		if ( storePtr == nullptr )
		{
			return false;
		}

		return storePtr->arrayExists(variableName);
	}

	bool
	Settings::storeExists (const std::string & key) const noexcept
	{
		std::string storeName{};

		const auto * storePtr = this->getStorePointer(key, storeName);

		if ( storePtr == nullptr )
		{
			return false;
		}

		return storePtr->subStoreExists(storeName);
	}

	std::string
	Settings::get (const std::string & key) const noexcept
	{
		std::string variableName{};

		const auto * storePtr = this->getStorePointer(key, variableName);

		/* The store and/or sub-store doesn't exist. */
		if ( storePtr == nullptr )
		{
			return {};
		}

		return storePtr->get(variableName);
	}

	std::string
	Settings::get (const std::string & key, const std::string & defaultValue) noexcept
	{
		std::string variableName{};

		return this->getStorePointer(key, variableName)->getOrSet(variableName, defaultValue);
	}

	std::vector< std::string >
	Settings::asStringList (const std::string & key) const noexcept
	{
		std::vector< std::string > list{};

		std::string variableName{};

		const auto * storePtr = this->getStorePointer(key, variableName);

		if ( storePtr != nullptr && !variableName.empty() )
		{
			const auto * variablePtr = storePtr->getArray(variableName);

			if ( variablePtr != nullptr )
			{
				std::copy(variablePtr->cbegin(), variablePtr->cend(), std::back_inserter(list));
			}
		}

		return list;
	}

	bool
	Settings::isArrayEmpty (const std::string & key) const noexcept
	{
		std::string variableName{};

		const auto * storePtr = this->getStorePointer(key, variableName);

		if ( storePtr == nullptr )
		{
			return true;
		}

		const auto * variablePtr = storePtr->getArray(variableName);

		if ( variablePtr == nullptr )
		{
			return true;
		}

		return variablePtr->empty();
	}

	bool
	Settings::onInitialize () noexcept
	{
		/* Checks the file presence, if not, it will be created and uses the default engine values. */
		if ( !m_filepath.exists() )
		{
			TraceWarning{ClassId} <<
				"Settings file '" << m_filepath << "' doesn't exist. "
				"Writing a new one ...";

			m_flags[SaveAtExit] = true;

			return true;
		}

		/* Reading the file ... */
		if ( !this->readFile(m_filepath) )
		{
			TraceError{ClassId} << "Unable to read settings file from '" << m_filepath << "' path !";

			m_flags[SaveAtExit] = false;

			return false;
		}

#ifdef DEBUG
		std::cout << *this << '\n';
#endif

		return true;
	}

	bool
	Settings::onTerminate () noexcept
	{
		if ( m_flags[SaveAtExit] )
		{
			if ( m_filepath.empty() )
			{
				TraceError{ClassId} << "File path is empty. Unable to save this settings file !";

				return false;
			}

			if ( !this->writeFile(m_filepath) )
			{
				TraceError{ClassId} << "Unable to write settings file to '" << m_filepath << "' !";

				return false;
			}
		}

		return true;
	}

	bool
	Settings::save () const noexcept
	{
		if ( m_filepath.empty() )
		{
			Tracer::warning(ClassId, "No filepath was used to read config !");

			return false;
		}

		return this->writeFile(m_filepath);
	}

	void
	Settings::clear () noexcept
	{
		m_store.clear();
	}

	std::ostream &
	operator<< (std::ostream & out, const Settings & obj)
	{
		using namespace std;

		std::stack< std::pair< std::string, const SettingStore * > > stores{};

		auto depth = 0UL;

		/* Sets the top Store */
		stores.emplace("Root", &obj.m_store);

		out << "\n" "[Core] Settings (" << obj.m_filepath << ") :" "\n";

		/* Crawling inside all stores. */
		while ( !stores.empty() )
		{
			const auto * store = stores.top().second;

			out << ' ';

			if ( depth > 0 )
			{
				for ( size_t i = 0; i < depth; i++ )
				{
					out << "----";
				}
			}

			out << '[' << stores.top().first << "]" "\n";

			/* Print every variable */
			for ( const auto & pair : store->variables() )
			{
				out << ' ';

				for ( size_t i = 0; i <= depth; i++ )
				{
					out << "----";
				}

				out << ' ' << pair.first << " = " << pair.second << '\n';
			}

			/* Print every arrays */
			for ( const auto & pair : store->arrays() )
			{
				out << ' ';

				for ( size_t i = 0; i <= depth; i++ )
				{
					out << "----";
				}

				out << ' ' << pair.first << " = [" << String::implode(pair.second, ", ") << "]" "\n";
			}

			/* Removing it from the queue. */
			stores.pop();

			/* Then load every sub stores from
			 * this store for the next loop cycle. */
			for ( const auto & pair : store->subStores() )
			{
				stores.emplace(pair.first, &(pair.second));
			}

			depth++;
		}

		return out;
	}

	std::string
	to_string (const Settings & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
