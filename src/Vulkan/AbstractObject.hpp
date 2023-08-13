/*
 * Emeraude/Vulkan/AbstractObject.hpp
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

#ifdef DEBUG
#define VK_TRACKING
#endif

/* C/C++ standard libraries. */
#include <array>
#include <string>
#ifdef VK_TRACKING
#include <map>
#endif

/* Third-party libraries. */
#include "Third-Party-Inclusion/vulkan.hpp"

namespace Emeraude::Vulkan
{
	/** @brief Base of all Vulkan API object. */
	class AbstractObject
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractObject (const AbstractObject & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractObject (AbstractObject && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractObject &
			 */
			AbstractObject & operator= (const AbstractObject & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractObject &
			 */
			AbstractObject & operator= (AbstractObject && copy) noexcept = default;

			/**
			 * @brief Destructs a base vulkan object.
			 */
			virtual ~AbstractObject ();

			/**
			 * @brief Sets an identifier to the vulkan to ease the debugging.
			 * @return void
			 */
			virtual void setIdentifier (const std::string & identifier) noexcept final;

			/**
			 * @brief Returns the vulkan object identifier.
			 * @return const char *
			 */
			[[nodiscard]]
			virtual const std::string & identifier () const noexcept final;

			/**
			 * @brief Returns whether the object is in video memory and usable.
			 * @return bool
			 */
			[[nodiscard]]
			bool isCreated () const noexcept;

#ifdef VK_TRACKING
			static std::map< void *, std::string > s_tracking; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables) NOTE : Debug purpose
#endif

		protected:

#ifdef VK_TRACKING
			/**
			 * @brief Constructs a base vulkan object.
			 */
			AbstractObject () noexcept;
#else
			/**
			 * @brief Constructs a base vulkan object.
			 */
			AbstractObject () noexcept = default;
#endif

			/**
			 * @brief For development purpose, this should be called by the child class constructor if everything is OK.
			 * @return void
			 */
			void setCreated () noexcept;

			/**
			 * @brief For development purpose, this should be called by the child class destructor if everything is OK.
			 * @return void
			 */
			void setDestroyed () noexcept;

		private:

			/* Flag names. */
			static constexpr auto Created = 0UL;
			static constexpr auto Destroyed = 1UL;

			std::string m_identifier{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*Created*/,
				false/*Destroyed*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
