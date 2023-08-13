/*
 * Emeraude/Vulkan/SharedBufferElementInterface.hpp
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

/* Local inclusions for inheritances. */

/* Local inclusions for usages. */

namespace Emeraude::Vulkan
{
	/**
	 * @brief The shared buffer element interface.
	 */
	class SharedBufferElementInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			SharedBufferElementInterface (const SharedBufferElementInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			SharedBufferElementInterface (SharedBufferElementInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return SharedBufferElementInterface &
			 */
			SharedBufferElementInterface & operator= (const SharedBufferElementInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return SharedBufferElementInterface &
			 */
			SharedBufferElementInterface & operator= (SharedBufferElementInterface && copy) noexcept = default;
			
			/**
			 * @brief Destructs the shared buffer element interface.
			 */
			virtual ~SharedBufferElementInterface () = default;

		protected:

			/** 
			 * @brief Constructs a shared buffer element interface.
			 */
			SharedBufferElementInterface () noexcept = default;
			
		private:


	};
}
