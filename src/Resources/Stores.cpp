/*
 * src/Resources/Stores.cpp
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

#include "Stores.hpp"

/* STL inclusions. */
#include <cstddef>
#include <fstream>
#include <vector>
#include <filesystem>
#include <regex>

/* Local inclusions. */
#include "Libs/FastJSON.hpp"
#include "Libs/Utility.hpp"
#include "Libs/IO/IO.hpp"
#include "PrimaryServices.hpp"
#include "BaseInformation.hpp"
#include "SettingKeys.hpp"

namespace EmEn::Resources
{
	using namespace EmEn::Libs;

	const size_t Stores::ClassUID{getClassUID(ClassId)};
	bool Stores::s_operationVerboseEnabled{false};
	bool Stores::s_downloadEnabled{true};

	Stores::Stores (PrimaryServices & primaryServices) noexcept
		: ServiceInterface(ClassId),
		m_primaryServices(primaryServices)
	{

	}

	size_t
	Stores::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	Stores::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	bool
	Stores::usable () const noexcept
	{
		return m_flags[ServiceInitialized];
	}

	const Stores::Store &
	Stores::store (const std::string & storeName) const noexcept
	{
		if ( m_stores.empty() )
		{
			Tracer::warning(ClassId, "There is no store at all !");

			return m_defaultStore;
		}

		const auto storeIt = m_stores.find(storeName);

		if ( storeIt == m_stores.cend() )
		{
			TraceWarning{ClassId} <<  "Store named '" << storeName << "' doesn't exist !";

			return m_defaultStore;
		}

		return storeIt->second;
	}

	bool
	Stores::onInitialize () noexcept
	{
		s_operationVerboseEnabled = m_primaryServices.settings().get< bool >(ResourcesShowInformationKey, DefaultResourcesShowInformation);
		s_downloadEnabled = m_primaryServices.settings().get< bool >(ResourcesDownloadEnabledKey, DefaultResourcesDownloadEnabled);

		const auto indexes = this->getResourcesIndexFiles();

		if ( indexes.empty() )
		{
			std::stringstream message{};

			message <<
				"No resources index available !" "\n"
				"Checked directories :" "\n";

			for ( auto directory : m_primaryServices.fileSystem().dataDirectories() )
			{
				message << directory.append(DataStores).string() << "\n";
			}

			TraceWarning{ClassId} << message;

			return false;
		}

		const auto verbose = m_primaryServices.settings().get< bool >(ResourcesShowInformationKey, DefaultResourcesShowInformation);

		m_registeredResources = 0;

		for ( const auto & filepath : indexes )
		{
			TraceInfo{ClassId} << "Loading resource index from file '" << filepath << "' ...";

			/* 1. Get raw JSON data from file */
			Json::Value root;

			if ( !FastJSON::getRootFromFile(filepath, root) )
			{
				TraceError{ClassId} << "Unable to parse the index file " << filepath << " !" "\n";

				continue;
			}

			/* 3. Register every stores */
			if ( !root.isMember(StoresKey) )
			{
				TraceError{ClassId} << "'" << StoresKey << "' key doesn't exist !";

				continue;
			}

			const auto & storesObject = root[StoresKey];

			if ( !storesObject.isObject() )
			{
				TraceError{ClassId} << "'" << StoresKey << "' key must be a JSON object !";

				continue;
			}

			const auto resourcesRead = this->parseStores(storesObject, verbose);

			TraceSuccess{ClassId} << resourcesRead << " resources added !";

			m_registeredResources += resourcesRead;
		}

		m_flags[ServiceInitialized] = true;

		return true;
	}

	bool
	Stores::onTerminate () noexcept
	{
		m_flags[ServiceInitialized] = false;

		m_defaultStore.clear();

		m_stores.clear();

		return true;
	}

	void
	Stores::update (const Json::Value & root, const std::string & name) noexcept
	{
		const auto verbose = m_primaryServices.settings().get< bool >(ResourcesShowInformationKey, DefaultResourcesShowInformation);

		if ( !root.isObject() )
		{
			Tracer::warning(ClassId, "It must be a JSON object to check for additional stores !");

			return;
		}

		if ( !root.isMember(StoresKey) )
		{
			return;
		}

		const auto & stores = root[StoresKey];

		if ( !stores.isObject() )
		{
			TraceError{ClassId} << "'" << StoresKey << "' key must be a JSON object !";

			return;
		}

		if ( verbose )
		{
			TraceInfo{ClassId} << "A '" << StoresKey << "' key is present in '" << name << "', adding new resources ...";
		}

		m_registeredResources += this->parseStores(stores, verbose);
	}

	std::string
	Stores::randomName (const std::string & storeName) const noexcept
	{
		const auto & resourceStore = this->store(storeName);

		const auto random = Utility::quickRandom< size_t >(0, resourceStore.size());

		return std::next(std::begin(resourceStore), static_cast< long >(random))->first;
	}

	bool
	Stores::isJSONData (const std::string & buffer) noexcept
	{
		return buffer.find('{') != std::string::npos;
	}

	std::vector< std::string >
	Stores::getResourcesIndexFiles () const noexcept
	{
		std::vector< std::string > indexes{};

		const std::regex indexMatchRule("ResourcesIndex.([0-9]{3}).json",std::regex_constants::ECMAScript);

		/* NOTE: For each data directory pointed by the file system, we will look for resource index files. */
		for ( auto dataStoreDirectory : m_primaryServices.fileSystem().dataDirectories() )
		{
			dataStoreDirectory.append(DataStores);

			if ( !IO::directoryExists(dataStoreDirectory) )
			{
				/* No "data-stores/" in this data directory. */
				continue;
			}

			for ( const auto & entry : std::filesystem::directory_iterator(dataStoreDirectory) )
			{
				if ( !is_regular_file(entry.path()) )
				{
					/* This entry is not a file. */
					continue;
				}

				const auto filepath = entry.path().string();

				if ( !std::regex_search(filepath, indexMatchRule) )
				{
					/* No resource index file in this "data-stores/" directory. */
					TraceWarning{ClassId} << "Directory '" << entry << "' do not contains any resource index file !";

					continue;
				}

				indexes.emplace_back(filepath);
			}
		}

		return indexes;
	}

	size_t
	Stores::parseStores (const Json::Value & storesObject, bool verbose) noexcept
	{
		size_t resourcesRegistered = 0;

		for ( auto storeIt = storesObject.begin(); storeIt != storesObject.end(); ++storeIt )
		{
			auto storeName = storeIt.name();

			/* Checks if the store is a JSON array, ie : "Meshes":[{},{},...] */
			if ( !storeIt->isArray() )
			{
				TraceError{ClassId} << "Store '" << storeName << "' isn't a JSON array !";

				continue;
			}

			/* Checks if we have to create the store or to complete it. */
			if ( !m_stores.contains(storeName) )
			{
				m_stores[storeName] = {};

				if ( verbose )
				{
					TraceInfo{ClassId} << "Initializing '" << storeName << "' store...";
				}
			}

			/* Crawling in resources definition. */
			for ( const auto & resourceDefinition : *storeIt )
			{
				/* Checks the data source to load it. */
				BaseInformation baseInformation{};

				if ( !baseInformation.parse(resourceDefinition) )
				{
					TraceError{ClassId} <<
						"Invalid resource in '" << storeName << "' store ! "
						"Skipping ...";

					continue;
				}

				/* Resource name starting with '+' is reserved by the engine. */
				if ( baseInformation.name().starts_with('+') )
				{
					TraceError{ClassId} <<
						"Resource name starting with '+' is reserved by the engine ! "
						"Skipping '" << baseInformation.name() << "' resource ...";

					continue;
				}

				/* Warns user if we erase an old resource named the same way. */
				if ( m_stores[storeName].contains(baseInformation.name()) )
				{
					TraceWarning{ClassId} <<
						"'" << baseInformation.name() << "' already exists in '" << storeName << "' store. "
						"It will be erased !";
				}

				/* Adds resource to store. */
				m_stores[storeName][baseInformation.name()] = baseInformation;

				resourcesRegistered++;

				if ( verbose )
				{
					TraceInfo{ClassId} << "Resource '" << baseInformation.name() << "' added to store '" << storeName << "'.";
				}
			}
		}

		return resourcesRegistered;
	}

	std::ostream &
	operator<< (std::ostream & out, const Stores & obj)
	{
		if ( obj.m_stores.empty() )
		{
			return out << "There is no available resource store !" "\n";
		}

		out << "Resources stores :" "\n";

		for ( const auto & [name, store] : obj.m_stores )
		{
			out << " - " << name << " (" << store.size() << " resources)" << '\n';
		}

		return out;
	}

	std::string
	to_string (const Stores & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
