/*
 * src/Resources/Stores.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <array>
#include <cstddef>
#include <map>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "BaseInformation.hpp"

/* Forward declarations. */
namespace Emeraude
{
	class PrimaryServices;
}

namespace Emeraude::Resources
{
	/**
	 * @brief The resource stores contains by type all resources available on disk by reading an index file.
	 * This only give the filepath to the actual resource.
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

			static bool s_operationVerboseEnabled;
			static bool s_downloadEnabled;

			/**
			 * @brief Constructs the resource stores.
			 * @param primaryServices A reference to primary services.
			 */
			explicit Stores (PrimaryServices & primaryServices) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc Libraries::ObservableTrait::is() const */
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
			 * @brief Updates resources store from another resource JSON definition.
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
			 * @brief Returns whether the string buffer is JSON data or not.
			 * @param buffer A reference to a string.
			 * @return bool
			 */
			[[nodiscard]]
			static bool isJSONData (const std::string & buffer) noexcept;

			/**
			* @brief STL streams printable object.
			* @param out A reference to the stream output.
			* @param obj A reference to the object to print.
			* @return std::ostream &
			*/
			friend std::ostream & operator<< (std::ostream & out, const Stores & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const Stores & obj) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Returns a list of resources index filepath.
			 * @return std::vector< std::string >
			 */
			[[nodiscard]]
			std::vector< std::string > getResourcesIndexFiles () const noexcept;

			/**
			 * @brief Parses a store JSON object to list available resources on disk.
			 * @param storesObject A reference to a json value.
			 * @param verbose Enable the reading verbosity in console.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t parseStores (const Json::Value & storesObject, bool verbose) noexcept;

			static constexpr auto StoresKey{"Stores"};

			/* Flag names */
			static constexpr auto ServiceInitialized{0UL};

			PrimaryServices & m_primaryServices;
			std::map< std::string, Store > m_stores;
			Store m_defaultStore;
			size_t m_registeredResources{0};
			std::array< bool, 8 > m_flags{
				false/*ServiceInitialized*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
