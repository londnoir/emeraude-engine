/*
 * src/Libs/Math/ShapeInterface.hpp
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
#include <type_traits>

namespace EmEn::Libs::Math
{
	/**
	 * @brief The abstract geometric shape class.
	 * @tparam data_t The type used for geometric distance and dimensions. Default float.
	 */
	template< typename data_t = float >
	requires (std::is_arithmetic_v< data_t >)
	class ShapeInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShapeInterface (const ShapeInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShapeInterface (ShapeInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return ShapeInterface &
			 */
			ShapeInterface & operator= (const ShapeInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return ShapeInterface &
			 */
			ShapeInterface & operator= (ShapeInterface && copy) noexcept = default;

			/**
			 * @brief Destructs the abstract shape.
			 */
			virtual ~ShapeInterface () = default;

		protected:

			/**
			 * @brief Constructs an abstract shape.
			 */
			ShapeInterface () noexcept = default;
	};
}
