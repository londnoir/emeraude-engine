/*
 * Emeraude/Resources/ResourceTrait.hpp
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
#include <set>
#include <string>

/* Local inclusions */
#include "NamedItem.hpp"
#include "FastJSON.hpp"
#include "FlagTrait.hpp"
#include "Observable.hpp"
#include "Path/File.hpp"

namespace Emeraude::Resources
{
	/**
	 * @brief This class describe a loadable resource with dependencies.
	 * @extends Libraries::NamedItem A resource is always named.
	 * @extends Libraries::FlagTrait A resource needs flags to change behavior of resource construction.
	 * @extends Libraries::Observable A resource is observable to keep track of loading states.
	 */
	class ResourceTrait : public Libraries::NamedItem, public Libraries::FlagTrait< uint32_t >, public Libraries::Observable
	{
		public:

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				LoadFinished,
				LoadFailed,
				/* Enumeration boundary. */
				MaxEnum
			};

			/** @brief This enum define every stages of resource loading. */
			enum class Status: int
			{
				/* This is the status of a new resource instanciation. */
				Unloaded = 0,
				/* Define a resource being attached with dependencies. */
				Enqueuing = 1,
				/* Define a resource being manually attached with dependencies. */
				ManualEnqueuing = 2,
				/* Define a resource being loaded.
				 * NOTE: In this stage, this is no more possible to add new dependency. */
				Loading = 3,
				/* Define a resource fully loaded with all dependencies. */
				Loaded = 4,
				/* Define a resource impossible to load. */
				Failed = 5
			};

			/**
			 * @brief Returns whether the resource is the top of the loadable chain of objects.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isTopResource () const noexcept final;

			/**
			 * @brief Returns the number of dependencies still waiting to be loaded.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t dependencyCount () const noexcept final;

			/**
			 * @brief Returns whether this resource object is newly created and no loading is currently occurs.
			 * @note This method is useful when using Container::getOrCreate() with a resource.
			 * @warning If you want to know if the resource is not yet loaded, use "!AbstractChainableLoading::isLoaded()".
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isUnloaded () const noexcept final;

			/**
			 * @brief Returns whether this resource is loading.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isLoading () const noexcept final;

			/**
			 * @brief Returns whether this resource is loaded.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isLoaded () const noexcept final;

			/**
			 * @brief Enables the manual loading of the resource.
			 * @note This method will fails if the resource is currently loading in automatic mode.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool enableManualLoading () noexcept final;

			/**
			 * @brief Sets this resource status in manual loading mode.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool setManualLoadSuccess (bool status) noexcept final;

			/**
			 * @brief Returns the current status of the resource.
			 * @return Status
			 */
			[[nodiscard]]
			virtual Status status () const noexcept final;

			/**
			 * @brief Declares the resource is using the direct loading mode.
			 * @return void
			 */
			virtual void setDirectLoadingHint () noexcept final;

			/**
			 * @brief Returns the label of resource class.
			 * @return const char *
			 */
			[[nodiscard]]
			virtual const char * classLabel () const noexcept = 0;

			/**
			 * @brief Loads a fully functional dummy resource.
			 * @return bool
			 */
			virtual bool load () noexcept = 0;

			/**
			 * @brief Loads a resource from a disk file.
			 * @note If not overridden, this method will open the file and tries to read a JSON data and call the load(data) after.
			 * @param filepath The reference to a file path to the location of the resource.
			 * @return bool
			 */
			virtual bool load (const Libraries::Path::File & filepath) noexcept;

			/**
			 * @brief Loads a resource from a JsonCPP object.
			 * @param data A reference to a JsonCPP object.
			 * @return bool
			 */
			virtual bool load (const Json::Value & data) noexcept = 0;

		protected:

			/**
			 * @brief Constructs a resource.
			 * @param resourceName A reference to a string.
			 * @param flagBits The generic resource flag bits.
			 */
			ResourceTrait (const std::string & resourceName, uint32_t flagBits) noexcept;

			/**
			 * @brief Destructs the resource.
			 */
			~ResourceTrait () override;

			/**
			 * @brief Returns whether the resource use direct loading mode from manager.
			 * @return Status
			 */
			[[nodiscard]]
			virtual bool isDirectLoading () const noexcept final;

			/**
			 * @brief Sets the status of this resource to Status::Loading.
			 * @warning If this method return false, you should stop the loading.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool beginLoading () noexcept final;

			/**
			 * @brief Adds a new dependency to this loading object.
			 * @note If the sub resource is already loaded, it won't be added.
			 * @param dependency A point to the dependency.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool addDependency (ResourceTrait * dependency) noexcept final;

			/**
			 * @brief Sets the current status of loading by the inherited class.
			 * @note If status is Status::Loaded, this will return true.
			 * @param status Set the resource loading status.
			 * @return bool
			 */
			virtual bool setLoadSuccess (bool status) noexcept final;

			/**
			 * @brief This event is called when every dependencies are loaded.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool onDependenciesLoaded () noexcept = 0;

		private:

			/**
			 * @brief This private method is called from a child resource through m_parents
			 * set to relaunch the parent resource dependencies check.
			 * @param dependency A pointer to the loaded dependency. Suitable to unlink the resource from dependency set.
			 * @return void
			 */
			void dependencyLoaded (ResourceTrait * dependency) noexcept;

			/**
			 * @brief Checks this resource for every dependency below it. If everything is loaded, the method launch
			 * a parent check or if this resource is a top level, the final call to AbstractChainableLoading::onDependenciesLoaded()
			 * to notice the resource is available.
			 * @return void
			 */
			void checkDependencies () noexcept;

			/**
			 * @brief This is the real method that begin the first stage of resource loading.
			 * @param manual Boolean that denote if the status will be Enqueuing or ManualEnqueuing.
			 * @return bool
			 */
			[[nodiscard]]
			bool initializeEnqueuing (bool manual) noexcept;

			std::set< ResourceTrait * > m_parents{};
			std::set< ResourceTrait * > m_dependencies{};
			Status m_status = Status::Unloaded;
			mutable std::mutex m_checkAccess{};
			bool m_directLoad = false;
	};
}
