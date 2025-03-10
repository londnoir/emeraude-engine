/*
 * src/Libraries/Math/Line.hpp
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
#include <iostream>
#include <sstream>
#include <string>

/* Local inclusions. */
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief Class to design a line in space.
	 * @tparam data_t The precision type.
	 * @note : Equation is "y = ax + b"
	 */
	template< typename data_t = float >
	requires (std::is_arithmetic_v< data_t >)
	class Line final
	{
		public:

			/**
			 * @brief Constructs a line.
			 */
			Line () noexcept = default;

			/**
			 * @brief Constructs a line.
			 * @param a
			 * @param b
			 */
			Line (data_t a, data_t b) noexcept
				: m_a(a), m_b(b)
			{

			}

			/**
			 * @brief Constructs a line.
			 * @param a
			 * @param b
			 */
			Line (const Vector< 2, data_t > & a, const Vector< 2, data_t > & b) noexcept
			{
				this->findComponents(a[Vector< 2, data_t >::X], a[Vector< 2, data_t >::Y], b[Vector< 2, data_t >::X], b[Vector< 2, data_t >::Y]);
			}

			/**
			 * @brief Constructs a line.
			 * @param ax
			 * @param ay
			 * @param bx
			 * @param by
			 */
			Line (data_t ax, data_t ay, data_t bx, data_t by) noexcept
			{
				this->findComponents(ax, ay, bx, by);
			}

			/**
			 * @brief Sets the point A.
			 * @param a The point a.
			 * @return void
			 */
			void
			setA (data_t a) noexcept
			{
				m_a = a;
			}

			/**
			 * @brief Sets the point B.
			 * @param b The point b.
			 * @return void
			 */
			void
			setB (data_t b) noexcept
			{
				m_b = b;
			}

			/**
			 * @brief Returns the point A.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			a () const noexcept
			{
				return m_a;
			}

			/**
			 * @brief Returns the point B.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			b () const noexcept
			{
				return m_b;
			}

			/**
			 * @brief Finds the intersection between two line.
			 * @param ax
			 * @param ay
			 * @param bx
			 * @param by
			 * @param cx
			 * @param cy
			 * @param dx
			 * @param dy
			 * @return Vector< 2, data_t >
			 */
			static
			Vector< 2, data_t >
			findIntersection (data_t ax, data_t ay, data_t bx, data_t by, data_t cx, data_t cy, data_t dx, data_t dy) noexcept
			{
				Vector< 2, data_t > intersection{};

				data_t a = (ax * by - ay * bx);
				data_t b = (cx * dy - cy * dx);
				data_t det = (ax - bx) * (cy - dy) - (ay - by) * (cx - dx);

				intersection[X] = (a * (cx - dx) - (ax - bx) * b) / det;
				intersection[Y] = (a * (cy - dy) - (ay - by) * b) / det;

				return intersection;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Line & obj) noexcept
			{
				return out << "Line data :" "\n"
					"Point A : " << obj.m_a << "\n"
					"Point B : " << obj.m_b << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Line & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			/**
			 * @brief Finds components A and B.
			 * @param ax
			 * @param ay
			 * @param bx
			 * @param by
			 * @return void
			 */
			void
			findComponents (data_t ax, data_t ay, data_t bx, data_t by) noexcept
			{
				m_a = (by - ay) / (bx - ax);
				m_b = -(m_a * bx) + by;
			}

			data_t m_a = 0;
			data_t m_b = 0;
	};
}
