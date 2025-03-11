/*
 * src/Libs/Math/Circle.hpp
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
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

/* Local inclusions for inheritances. */
#include "Shape2DInterface.hpp"

/* Local inclusions for usages. */
#include "Base.hpp"
#include "Vector.hpp"

namespace EmEn::Libs::Math
{
	/**
	 * @brief Defines a geometric circle.
	 * @tparam data_t The type used for geometric distance and dimensions. Default float.
	 * @extends EmEn::Libs::Math::Shape2DInterface This is a 2D shape.
	 */
	template< typename data_t = float > requires (std::is_floating_point_v< data_t >)
	class Circle final : public Shape2DInterface< data_t >
	{
		public:

			/**
			 * @brief Constructs a circle.
			 * @param radius The initial radius. Default 0.
			 * @param position A reference to a vector. Default origin.
			 */
			explicit
			Circle (data_t radius = 0, const Vector< 2, data_t > & position = {}) noexcept
				: m_position(position), m_radius(radius)
			{

			}

			/** @copydoc EmEn::Libs::Math::Shape2DInterface::getPerimeter() */
			[[nodiscard]]
			data_t
			getPerimeter () const noexcept override
			{
				return circleCircumference(m_radius);
			}

			/** @copydoc EmEn::Libs::Math::Shape2DInterface::getArea() */
			[[nodiscard]]
			data_t
			getArea () const noexcept override
			{
				return circleArea(m_radius);
			}

			/**
			 * @brief Sets the position of the circle in space.
			 * @param position A reference to a vector.
			 */
			void
			setPosition (const Vector< 2, data_t > & position) noexcept
			{
				m_position = position;
			}

			/**
			 * @brief Returns the position of the circle in space.
			 * @return const Vector< 2, data_t > &
			 */
			[[nodiscard]]
			const Vector< 2, data_t > &
			position () const noexcept
			{
				return m_position;
			}

			/**
			 * @brief Sets the radius of the circle.
			 * @param radius The radius in engine metrics.
			 */
			void
			setRadius (data_t radius) noexcept
			{
				m_radius = std::abs(radius);
			}

			/**
			 * @brief Returns the radius of the circle in engine metrics.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			radius () const noexcept
			{
				return m_radius;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Circle & obj) noexcept
			{
				return out << "Circle data :\n"
					"Position : " << obj.m_position << "\n"
					"Radius : " << obj.m_radius << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Circle & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			Vector< 2, data_t > m_position;
			data_t m_radius;
	};
}
