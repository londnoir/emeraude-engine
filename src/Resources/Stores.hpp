/*
 * Emeraude/Resources/Stores.hpp
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
#include <string>
#include <map>
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "emeraude_config.hpp"
#include "FileSystem.hpp"
#include "Settings.hpp"
#include "String.hpp"
#include "BaseInformation.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/json.hpp"

namespace Emeraude::Resources
{
	/**
	 * @brief This will parse and hold every local resources.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class Stores final : public ServiceInterface
	{
		public:

			using Store = std::map< std::string, BaseInformation >;

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ResourcesStoresService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			static constexpr auto DataStores = "datastores";

			/* Settings keys */
			static constexpr auto InitializationVerboseEnabledKey = "Resources/InitializationVerboseEnabled";
			static constexpr auto DefaultInitializationVerboseEnabled = BOOLEAN_FOLLOWING_DEBUG;
			static constexpr auto UpdateVerboseEnabledKey = "Resources/UpdateVerboseEnabled";
			static constexpr auto DefaultUpdateVerboseEnabled = BOOLEAN_FOLLOWING_DEBUG;
			static constexpr auto OperationVerboseEnabledKey = "Resources/OperationVerboseEnabled";
			static constexpr auto DefaultOperationVerboseEnabled = BOOLEAN_FOLLOWING_DEBUG;
			static constexpr auto DownloadEnabledKey = "Resources/DownloadEnabled";
			static constexpr auto DefaultDownloadEnabled = true;

			static bool s_operationVerboseEnabled;
			static bool s_downloadEnabled;

			/**
			 * @brief Constructs the resource stores.
			 * @param arguments A reference to Arguments.
			 * @param fileSystem The file system management object to deal with configuration files.
			 * @param coreSettings A reference to the core settings.
			 */
			Stores (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Returns a reference to a named store.
			 * @param storeName A reference to a string for the store name.
			 * @return const Store & store
			 */
			[[nodiscard]]
			const Store & store (const std::string & storeName) const noexcept;

			/**
			 * @brief Updates resources store from an other resource JSON definition.
			 * @param root The resource JSON object.
			 * @param name The name of the object. Default "unknown".
			 */
			void update (const Json::Value & root, const std::string & name = "Unknown") noexcept;

			/**
			 * @brief Returns a random resource from a named store.
			 * @param storeName A reference to a string for the store name.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string randomName (const std::string & storeName) const noexcept;

			/**
			 * @brief Returns the directory of a resource store.
			 * @param storeName A point to a C-string for the store name.
			 * @return Directory
			 */
			[[nodiscard]]
			static Libraries::Path::Directory namedStore (const char * storeName) noexcept;

			/**
			 * @brief Returns wheter the string buffer is JSON data or not.
			 * @param buffer A reference to a string.
			 * @return bool
			 */
			[[nodiscard]]
			static bool isJSONData (const std::string & buffer) noexcept;

		private:

			static constexpr auto ResourceIndexFiles = "ResourcesIndex.???.json";
			static constexpr auto StoresKey = "Stores";

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief getResourcesIndexFiles
			 * @return std::vector< std::string >
			 */
			[[nodiscard]]
			std::vector< std::string > getResourcesIndexFiles () noexcept;

			/**
			 * @brief parseStores
			 * @param storesObject
			 * @param verbose
			 * @return size_t
			 */
			[[nodiscard]]
			size_t parseStores (const Json::Value & storesObject, bool verbose) noexcept;

			const Arguments & m_arguments;
			const FileSystem & m_fileSystem;
			Settings & m_coreSettings;
			std::map< std::string, Store > m_stores{};
			Store m_defaultStore{};
			size_t m_registeredResources = 0;
	};
}
