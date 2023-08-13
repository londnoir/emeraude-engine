/*
 * Emeraude/ServiceInterface.hpp
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
#include <vector>

/* Local inclusions for inheritances. */
#include "NamedItem.hpp"
#include "Observable.hpp"

namespace Emeraude
{
	/**
	 * @brief The service interface.
	 * @note A service cannot be duplicated and acts like a singleton.
	 * @extends Libraries::NamedItem Each service have a name.
	 * @extends Libraries::Observable Each service should be observable.
	 */
	class ServiceInterface : public Libraries::NamedItem, public Libraries::Observable
	{
		public:

			/** @brief Service common notification code. */
			enum NotificationCode
			{
				ServiceUp,
				ServiceDown,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Destructs the service.
			 */
			~ServiceInterface () override = default;

			/**
			 * @brief Copy constructor.
			 * @note A service cannot be duplicated.
			 * @param copy A reference to the copied instance.
			 */
			ServiceInterface (const ServiceInterface & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @note A service cannot be duplicated.
			 * @param copy A reference to the copied instance.
			 */
			ServiceInterface (ServiceInterface && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @note A service cannot be duplicated.
			 * @param copy A reference to the copied instance.
			 */
			ServiceInterface & operator= (const ServiceInterface & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @note A service cannot be duplicated.
			 * @param copy A reference to the copied instance.
			 */
			ServiceInterface & operator= (ServiceInterface && copy) noexcept = delete;

			/**
			 * @brief Starts the service.
			 * @param enabledServices A reference to auto register the service for shutdown.
			 * @return bool.
			 */
			virtual bool initialize (std::vector< ServiceInterface * > & enabledServices) noexcept final;

			/**
			 * @brief Terminates the service.
			 * @return bool.
			 */
			virtual bool terminate () noexcept final;

			/**
			 * @brief Returns whether the service is up and available.
			 * @return bool.
			 */
			[[nodiscard]]
			virtual bool usable () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a service.
			 * @param serviceInstanceName The name of the service for print information.
			 */
			explicit ServiceInterface (const char * serviceInstanceName) noexcept;

			/**
			 * @brief This method must be override by the final service on initialization.
			 * @return bool
			 */
			virtual bool onInitialize () noexcept = 0;

			/**
			 * @brief This method must be override by the final service on termination.
			 * @return bool
			 */
			virtual bool onTerminate () noexcept = 0;
	};
}
