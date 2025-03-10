/*
 * src/MemoryAllocator.hpp
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

#pragma once

/* STL inclusions. */
#include <array>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

namespace Emeraude
{
	/**
	 * @brief The memory allocator service class.
	 * @TODO Make a way to allocate huge part of memory to share between local usage in the engine.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class MemoryAllocator final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanMemoryAllocatorService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** 
			 * @brief Constructs the memory allocator.
			 */
			MemoryAllocator () noexcept;

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
