/*
 * src/PlatformManager.hpp
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

/* STL inclusions. */
#include <array>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Forward declarations. */
namespace Emeraude
{
	class PrimaryServices;
}

namespace Emeraude
{
	/**
	 * @brief The platform manager service class initialize check Vulkan and initialize GLFW with it.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class PlatformManager final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PlatformManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs the platform manager.
			 * @param primaryServices A reference to primary services.
			 */
			explicit PlatformManager (PrimaryServices & primaryServices) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/* Flag names */
			static constexpr auto ServiceInitialized{0UL};
			static constexpr auto ShowInformation{1UL};

			PrimaryServices & m_primaryServices;
			std::array< bool, 8 > m_flags{
				false/*ServiceInitialized*/,
				false/*ShowInformation*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
