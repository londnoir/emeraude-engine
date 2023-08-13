/*
 * Emeraude/User.hpp
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
#include <string>

/* Local inclusion for inheritances */
#include "ServiceInterface.hpp"

namespace Emeraude
{
	class Settings;

	/**
	 * @brief The user service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class User final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"UserService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs an user.
			 * @param applicationSettings
			 */
			explicit User (Settings & applicationSettings) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Sets an user identification.
			 * @param identifier An integer like ID from external platform.
			 */
			void setUserID (uint64_t identifier) noexcept;

			/**
			 * @brief Sets the user name.
			 * @param username A reference to a string.
			 */
			void setUsername (const std::string & username) noexcept;

			/**
			 * @brief Returns the third-party user id.
			 * @return uint64_t
			 */
			[[nodiscard]]
			uint64_t userID () const noexcept;

			/**
			 * @brief Returns the user name.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & username () const noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			Settings & m_applicationSettings;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			uint64_t m_userID = 0;
			std::string m_username{"john.doe"};
	};
}
