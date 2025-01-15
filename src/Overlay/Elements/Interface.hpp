/*
 * src/Overlay/Elements/Interface.hpp
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

namespace Emeraude::Overlay::Elements
{
	/**
	 * @brief The UI input interface.
	 */
	class UIInputInterface
	{
		public:

			enum class Status
			{
				Normal,
				Over,
				Active,
				Disabled
			};

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			UIInputInterface (const UIInputInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			UIInputInterface (UIInputInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return UIInputInterface &
			 */
			UIInputInterface & operator= (const UIInputInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return UIInputInterface &
			 */
			UIInputInterface & operator= (UIInputInterface && copy) noexcept = default;

			/** 
			 * @brief Destructs the UI input interface.
			 */
			virtual ~UIInputInterface() = default;

		protected:

			/** 
			 * @brief Constructs an UI input interface.
			 */
			UIInputInterface () noexcept = default;
	};
}
