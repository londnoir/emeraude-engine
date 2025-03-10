/*
 * src/Libraries/Math/Shape2DInterface.hpp
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

/* Local inclusions for inheritances. */
#include "ShapeInterface.hpp"

namespace Libraries::Math
{
	/**
	 * @brief The abstract 2D shape class.
	 * @tparam data_t The type used for geometric distance and dimensions. Default float.
	 * @extends Libraries::Math::ShapeInterface This is a geometric shape.
	 */
	template< typename data_t = float >
	requires (std::is_arithmetic_v< data_t >)
	class Shape2DInterface : public ShapeInterface< data_t >
	{
		public:

			/**
			 * @brief Returns the perimeter of the 2D shape.
			 * @return data_t
			 */
			[[nodiscard]]
			virtual data_t getPerimeter () const noexcept = 0;

			/**
			 * @brief Returns the area of the 2D shape.
			 * @return data_t
			 */
			[[nodiscard]]
			virtual data_t getArea () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs an abstract 2D shape.
			 */
			Shape2DInterface () noexcept = default;
	};
}
