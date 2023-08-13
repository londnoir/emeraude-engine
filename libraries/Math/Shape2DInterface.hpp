/*
 * Libraries/Math/Shape2DInterface.hpp
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

/* Local inclusions for inheritances. */
#include "ShapeInterface.hpp"

namespace Libraries::Math
{
	/**
	 * @brief The abstract 2D shape class.
	 * @tparam data_t The type used for geometric distance and dimensions. Default float.
	 * @extends Libraries::Math::ShapeInterface This is a geometric shape.
	 */
	template< typename data_t = float, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	class Shape2DInterface : public ShapeInterface< data_t >
	{
		public:

			/**
			 * @brief Returns the perimeter of the 2D shape.
			 * @return data_t
			 */
			[[maybe_unused]]
			[[nodiscard]]
			virtual data_t getPerimeter () const noexcept = 0;

			/**
			 * @brief Returns the area of the 2D shape.
			 * @return data_t
			 */
			[[maybe_unused]]
			[[nodiscard]]
			virtual data_t getArea () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs an abstract 2D shape.
			 */
			Shape2DInterface () noexcept = default;
	};
}
