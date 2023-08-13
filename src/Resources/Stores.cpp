/*
 * Emeraude/Resources/Stores.cpp
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

#include "Stores.hpp"

/* C/C++ standard libraries. */
#include <fstream>
#include <iostream> // DEV
#ifndef __WIN64__
#include <glob.h>
#endif

/* Local inclusions */
#include "Path/Path.hpp"
#include "Tracer.hpp"

namespace Emeraude::Resources
{
	using namespace Libraries;

	const size_t Stores::ClassUID{Observable::getClassUID()};
	bool Stores::s_operationVerboseEnabled{BOOLEAN_FOLLOWING_DEBUG};
	bool Stores::s_downloadEnabled{true};

	Stores::Stores (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_fileSystem(fileSystem), m_coreSettings(coreSettings)
	{

	}

	bool
	Stores::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Stores::usable () const noexcept
	{
		return m_registeredResources > 0;
	}

	const Stores::Store &
	Stores::store (const std::string & storeName) const noexcept
	{
		if ( m_stores.empty() )
		{
			Tracer::warning(ClassId, "There is no store at all !");

			return m_defaultStore;
		}

		auto storeIt = m_stores.find(storeName);

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
		s_operationVerboseEnabled = m_coreSettings.getAs< bool >(OperationVerboseEnabledKey, DefaultOperationVerboseEnabled);
		s_downloadEnabled = m_coreSettings.getAs< bool >(Stores::DownloadEnabledKey, Stores::DefaultDownloadEnabled);

		const auto indexes = this->getResourcesIndexFiles();

		if ( indexes.empty() )
		{
			Tracer::warning(ClassId, "No resources index available !");

			return false;
		}

		const auto verbose = m_coreSettings.getAs< bool >(InitializationVerboseEnabledKey, DefaultInitializationVerboseEnabled);

		m_registeredResources = 0;

		for ( auto & indexFilepath : indexes )
		{
			TraceInfo{ClassId} << "Reading resource index '" << indexFilepath << "' ...";

			/* 1. Get raw JSON data from file */
			Json::CharReaderBuilder builder;

			std::ifstream json(indexFilepath, std::ifstream::binary);

			Json::Value root;

			std::string errors;

			if ( !Json::parseFromStream(builder, json, &root, &errors) )
			{
				TraceError{ClassId} << "Unable to parse JSON file ! Errors :\n" << errors;

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

		return true;
	}

	bool
	Stores::onTerminate () noexcept
	{
		/* FIXME: Maybe save new local resources in the file ? */

		m_defaultStore.clear();

		m_stores.clear();

		return true;
	}

	void
	Stores::update (const Json::Value & root, const std::string & name) noexcept
	{
		const auto verbose = m_coreSettings.getAs< bool >(UpdateVerboseEnabledKey, DefaultUpdateVerboseEnabled);

		if ( !root.isObject() )
		{
			Tracer::warning(ClassId, "It must be a JSON object to check for additional stores !");

			return;
		}

		if ( !root.isMember(StoresKey) )
			return;

		const auto & stores = root[StoresKey];

		if ( !stores.isObject() )
		{
			TraceError{ClassId} << "'" << StoresKey << "' key must be a JSON object !";

			return;
		}

		if ( verbose )
			TraceInfo{ClassId} << "A '" << StoresKey << "' key is present in '" << name << "', adding new resources ...";

		m_registeredResources += this->parseStores(stores, verbose);
	}

	std::string
	Stores::randomName (const std::string & storeName) const noexcept
	{
		const auto & resourceStore = this->store(storeName);

		return std::next(std::begin(resourceStore), Utility::trueRandom(0UL, resourceStore.size()))->first;
	}

	Path::Directory
	Stores::namedStore (const char * storeName) noexcept
	{
		std::string directory{};
		directory += DataStores;
		directory += Libraries::Path::Separator;
		directory += storeName;

		return FileSystem::instance()->dataDirectory(directory);
	}

	bool
	Stores::isJSONData (const std::string & buffer) noexcept
	{
		return buffer.find('{') != std::string::npos;
	}

	std::vector< std::string >
	Stores::getResourcesIndexFiles () noexcept
	{
		std::vector< std::string > indexes;

		for ( auto directory : m_fileSystem.dataDirectoriesList() )
		{
			directory.append(DataStores);

#ifdef __WIN64__
			/* FIXME: Ugly solution caused by unavailability of glob.h with mingw-w64 */
			for ( auto index = 0; index < 9; index++ )
			{
				auto indexFile = Path::File(directory, "ResourcesIndex.00" + std::to_string(index) + ".json");

				if ( indexFile.exists() )
					indexes.emplace_back(indexFile.to_string());
			}
#else
			/* Where to find every resource. */
			const Path::File indexGlobRule{directory, ResourceIndexFiles};

			TraceInfo{ClassId} << "Looking for resource index files with rule '" << indexGlobRule << "' ...";

			{
				glob_t files{};

				glob(to_string(indexGlobRule).c_str(), GLOB_TILDE, nullptr, &files);

				for ( size_t index = 0; index < files.gl_pathc; ++index )
					indexes.emplace_back(files.gl_pathv[index]);

				globfree(&files);
			}
#endif
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
					TraceInfo{ClassId} << "Initializing '" << storeName << "' store...";
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
				if ( m_stores[storeName].find(baseInformation.name()) != m_stores[storeName].cend() )
					TraceWarning{ClassId} <<
						"'" << baseInformation.name() << "' already exists in '" << storeName << "' store. "
						"It will be erased !";

				/* Adds resource to store. */
				m_stores[storeName][baseInformation.name()] = baseInformation;

				resourcesRegistered++;

				if ( verbose )
					TraceInfo{ClassId} << "Resource '" << baseInformation.name() << "' added to store '" << storeName << "'.";
			}
		}

		return resourcesRegistered;
	}
}
