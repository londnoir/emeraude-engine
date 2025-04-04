/*
 * src/Libs/Math/Rectangle.hpp
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
#include <ostream>
#include <array>
#include <sstream>
#include <string>
#include <type_traits>

/* Local inclusions for inheritances. */
#include "Shape2DInterface.hpp"

/* Local inclusions for usages. */
#include "Vector.hpp"

namespace EmEn::Libs::Math
{
	/**
	 * @brief Defines a geometric rectangle.
	 * @tparam data_t The type used for geometric distance and dimensions. Default float.
	 * @extends EmEn::Libs::Math::Shape2DInterface This is a 2D shape.
	 */
	template< typename data_t = float >
	requires (std::is_arithmetic_v< data_t >)
	class Rectangle final : public Shape2DInterface< data_t >
	{
		public:

			static constexpr auto OffsetX{0UL};
			static constexpr auto OffsetY{1UL};
			static constexpr auto Width{2UL};
			static constexpr auto Height{3UL};

			/**
			 * @brief Constructs a default rectangle.
			 * @note The position will be 0,0 and width/height will be 1.0.
			 */
			Rectangle () noexcept = default;

			/**
			 * @brief Constructs a rectangle with dimensions.
			 * @param width The width of the rectangle.
			 * @param height The height of the rectangle.
			 */
			Rectangle (data_t width, data_t height) noexcept
				: m_data({0, 0, width, height})
			{

			}

			/**
			 * @brief Constructs a rectangle with position and dimensions.
			 * @param positionX The left position of the rectangle.
			 * @param positionY The top position of the rectangle.
			 * @param width The width of the rectangle.
			 * @param height The height of the rectangle.
			 */
			Rectangle (data_t positionX, data_t positionY, data_t width, data_t height) noexcept
				: m_data({positionX, positionY, width, height})
			{

			}

			/** @copydoc EmEn::Libs::Math::Shape2DInterface::getPerimeter() */
			[[nodiscard]]
			data_t
			getPerimeter () const noexcept override
			{
				return (this->width() + this->height()) * 2;
			}

			/** @copydoc EmEn::Libs::Math::Shape2DInterface::getArea() */
			[[nodiscard]]
			data_t
			getArea () const noexcept override
			{
				return this->width() * this->height();
			}

			/**
			 * @brief operator >
			 * @param operand A reference to another rectangle.
			 * @return bool
			 */
			bool
			operator> (const Rectangle< data_t > & operand) const noexcept
			{
				return m_data[Width] * m_data[Height] > operand.m_data[Width] * operand.m_data[Height];
			}

			/**
			 * @brief operator >=
			 * @param operand A reference to another rectangle.
			 * @return bool
			 */
			bool
			operator>= (const Rectangle< data_t > & operand) const noexcept
			{
				return m_data[Width] * m_data[Height] >= operand.m_data[Width] * operand.m_data[Height];
			}

			/**
			 * @brief operator <
			 * @param operand A reference to another rectangle.
			 * @return bool
			 */
			bool
			operator< (const Rectangle< data_t > & operand) const noexcept
			{
				return m_data[Width] * m_data[Height] < operand.m_data[Width] * operand.m_data[Height];
			}

			/**
			 * @brief operator <=
			 * @param operand A reference to another rectangle.
			 * @return bool
			 */
			bool
			operator<= (const Rectangle< data_t > & operand) const noexcept
			{
				return m_data[Width] * m_data[Height] <= operand.m_data[Width] * operand.m_data[Height];
			}

			/**
			 * @brief setOffsetX
			 * @param value
			 * @return void
			 */
			void
			setOffsetX (data_t value) noexcept
			{
				m_data[OffsetX] = value;
			}

			/**
			 * @brief setOffsetY
			 * @param value
			 * @return void
			 */
			void
			setOffsetY (data_t value) noexcept
			{
				m_data[OffsetY] = value;
			}

			/**
			 * @brief setWidth
			 * @param value
			 * @return void
			 */
			void
			setWidth (data_t value) noexcept
			{
				m_data[Width] = value;
			}

			/**
			 * @brief setHeight
			 * @param value
			 * @return void
			 */
			void
			setHeight (data_t value) noexcept
			{
				m_data[Height] = value;
			}

			/**
			 * @brief move
			 * @param x
			 * @param y
			 * @return void
			 */
			void
			move (data_t x, data_t y) noexcept
			{
				m_data[OffsetX] += x;
				m_data[OffsetY] += y;
			}

			/**
			 * @brief modifyWidthBy
			 * @param value
			 * @return void
			 */
			void
			modifyWidthBy (data_t value) noexcept
			{
				m_data[Width] += value;
			}

			/**
			 * @brief modifyHeightBy
			 * @param value
			 * @return void
			 */
			void
			modifyHeightBy (data_t value) noexcept
			{
				m_data[Height] += value;
			}

			/**
			 * @brief reset
			 * @return void
			 */
			void
			reset () noexcept
			{
				m_data = {{0, 0, 0, 0}};
			}

			/**
			 * @brief offsetX
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			offsetX () const noexcept
			{
				return m_data[OffsetX];
			}

			/**
			 * @brief offsetXb
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			offsetXb () const noexcept
			{
				return m_data[OffsetX] + m_data[Width]/* - 1*/;
			}

			/**
			 * @brief offsetY
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			offsetY () const noexcept
			{
				return m_data[OffsetY];
			}

			/**
			 * @brief offsetYb
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			offsetYb () const noexcept
			{
				return m_data[OffsetY] + m_data[Height]/* - 1*/;
			}

			/**
			 * @brief width
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			width () const noexcept
			{
				return m_data[Width];
			}

			/**
			 * @brief height
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			height () const noexcept
			{
				return m_data[Height];
			}

			/**
			 * @brief bottomLeft
			 * @return Vector< 2, data_t >
			 */
			[[nodiscard]]
			Vector< 2, data_t >
			bottomLeft () const noexcept
			{
				return {m_data[0], m_data[1]};
			}

			/**
			 * @brief bottomRight
			 * @return Vector< 2, data_t >
			 */
			[[nodiscard]]
			Vector< 2, data_t >
			bottomRight () const noexcept
			{
				return {this->offsetXb(), m_data[1]};
			}

			/**
			 * @brief topLeft
			 * @return Vector< 2, data_t >
			 */
			[[nodiscard]]
			Vector< 2, data_t >
			topLeft () const noexcept
			{
				return {m_data[0], this->offsetYb()};
			}

			/**
			 * @brief topRight
			 * @return Vector< 2, int >
			 */
			[[nodiscard]]
			Vector< 2, int >
			topRight () const noexcept
			{
				return {this->offsetXb(), this->offsetYb()};
			}

			/**
			 * @brief merge
			 * @param area
			 */
			void
			merge (const Rectangle< data_t > & area) noexcept
			{
				if ( !area.isValid() )
				{
					return;
				}

				if ( this->isValid() )
				{
					/* Operations in X. */
					if ( m_data[OffsetX] < area.m_data[OffsetX] )
					{
						if ( (m_data[OffsetX] + m_data[Width]) < (area.m_data[OffsetX] + area.m_data[Width]) )
						{
							m_data[Width] = (area.m_data[OffsetX] + area.m_data[Width]) - m_data[OffsetX];
						}
					}
					else
					{
						if ( (m_data[OffsetX] + m_data[Width]) > (area.m_data[OffsetX] + area.m_data[Width]) )
						{
							m_data[Width] = (m_data[OffsetX] + m_data[Width]) - area.m_data[OffsetX];
						}
						else
						{
							m_data[Width] = area.m_data[Width];
						}

						m_data[OffsetX] = area.m_data[OffsetX];
					}

					/* Operations in Y. */
					if ( m_data[OffsetY] < area.m_data[OffsetY] )
					{
						if ( (m_data[OffsetY] + m_data[Height]) < (area.m_data[OffsetY] + area.m_data[Height]) )
						{
							m_data[Height] = (area.m_data[OffsetY] + area.m_data[Height]) - m_data[OffsetY];
						}
					}
					else
					{
						if ( (m_data[OffsetY] + m_data[Height]) > (area.m_data[OffsetY] + area.m_data[Height]) )
						{
							m_data[Height] = (m_data[OffsetY] + m_data[Height]) - area.m_data[OffsetY];
						}
						else
						{
							m_data[Height] = area.m_data[Height];
						}

						m_data[OffsetY] = area.m_data[OffsetY];
					}
				}
				else
				{
					*this = area;
				}
			}

			/**
			 * @brief intersect
			 * @param area
			 * @return bool
			 */
			bool
			intersect (const Rectangle< data_t > & area) noexcept
			{
				if ( !this->isValid() || !area.isValid() )
				{
					return false;
				}

				if ( this->isIntersect(area) )
				{
					/* Operations in X. */
					if ( m_data[OffsetX] > area.m_data[OffsetX] )
					{
						if ( (m_data[OffsetX] + m_data[Width]) > (area.m_data[OffsetX] + area.m_data[Width]) )
						{
							m_data[Width] = (area.m_data[OffsetX] + area.m_data[Width]) - m_data[OffsetX];
						}
					}
					else
					{
						if ( (m_data[OffsetX] + m_data[Width]) < (area.m_data[OffsetX] + area.m_data[Width]) )
						{
							m_data[Width] = (m_data[OffsetX] + m_data[Width]) - area.m_data[OffsetX];
						}
						else
						{
							m_data[Width] = area.m_data[Width];
						}

						m_data[OffsetX] = area.m_data[OffsetX];
					}

					/* Operations in Y. */
					if ( m_data[OffsetY] > area.m_data[OffsetY] )
					{
						if ( (m_data[OffsetY] + m_data[Height]) > (area.m_data[OffsetY] + area.m_data[Height]) )
						{
							m_data[Height] = (area.m_data[OffsetY] + area.m_data[Height]) - m_data[OffsetY];
						}
					}
					else
					{
						if ( (m_data[OffsetY] + m_data[Height]) < (area.m_data[OffsetY] + area.m_data[Height]) )
						{
							m_data[Height] = (m_data[OffsetY] + m_data[Height]) - area.m_data[OffsetY];
						}
						else
						{
							m_data[Height] = area.m_data[Height];
						}

						m_data[OffsetY] = area.m_data[OffsetY];
					}

					return true;
				}

				this->reset();

				return false;
			}

			/**
			 * @brief isValid
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				/* NOTE: the area must positive. */
				return ( m_data[Width] > 0 && m_data[Height] > 0 );
			}

			/**
			 * @brief isOutside
			 * @param area A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isOutside (const Rectangle< data_t > & area) const noexcept
			{
				return (
					m_data[OffsetX] > area.offsetXb() ||
					area.m_data[OffsetX] > this->offsetXb() ||
					m_data[OffsetY] > area.offsetYb() ||
					area.m_data[OffsetY] > this->offsetYb()
				);
			}

			/**
			 * @brief isOutside
			 * @param width The width of the area. (x = 0)
			 * @param height The height of the area. (y = 0)
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isOutside (data_t width, data_t height) const noexcept
			{
				return m_data[OffsetX] > width && m_data[OffsetY] > height;
			}

			/**
			 * @brief isInside
			 * @param area A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isInside (const Rectangle< data_t > & area) const noexcept
			{
				if ( m_data[OffsetX] < area.m_data[OffsetX] )
				{
					return false;
				}

				if ( this->offsetXb() > area.offsetXb() )
				{
					return false;
				}

				if ( m_data[OffsetY] < area.m_data[OffsetY] )
				{
					return false;
				}

				if ( this->offsetYb() > area.offsetYb() )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief isInside
			 * @param width The width of the area. (x = 0)
			 * @param height The height of the area. (y = 0)
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isInside (data_t width, data_t height) const noexcept
			{
				return m_data[OffsetX] <= width && m_data[OffsetY] <= height;
			}

			/**
			 * @brief Returns whether the rectangle is intersecting an area.
			 * @param area A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isIntersect (const Rectangle< data_t > & area) const noexcept
			{
				/* Operation in X. */
				if ( m_data[OffsetX] < area.m_data[OffsetX] )
				{
					if ( this->offsetXb() < area.m_data[OffsetX] )
					{
						return false;
					}
				}
				else
				{
					if ( m_data[OffsetX] > area.offsetXb() )
					{
						return false;
					}
				}

				/* Operation in Y. */
				if ( m_data[OffsetY] < area.m_data[OffsetY] )
				{
					if ( this->offsetYb() < area.m_data[OffsetY] )
					{
						return false;
					}
				}
				else
				{
					if ( m_data[OffsetY] > area.offsetYb() )
					{
						return false;
					}
				}

				return true;
			}

			/**
			 * @brief Returns whether the rectangle is intersecting an area.
			 * @param width The width of the area. (x = 0)
			 * @param height The height of the area. (y = 0)
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isIntersect (data_t width, data_t height) const noexcept
			{
				return m_data[OffsetX] <= width && m_data[OffsetY] <= height;
			}

			/**
			 * @brief Returns whether the rectangle are inside an area.
			 * @param area A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			lieInside (const Rectangle< data_t > & area) const noexcept
			{
				if ( m_data[OffsetX] < area.m_data[OffsetX] )
				{
					return false;
				}

				if ( this->offsetXb() > area.offsetXb() )
				{
					return false;
				}

				if ( m_data[OffsetY] < area.m_data[OffsetY] )
				{
					return false;
				}

				if ( this->offsetYb() > area.offsetYb() )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Returns whether the rectangle are inside an area.
			 * @param width The width of the area. (x = 0)
			 * @param height The height of the area. (y = 0)
			 * @return bool
			 */
			[[nodiscard]]
			bool
			lieInside (data_t width, data_t height) const noexcept
			{
				return m_data[Width] <= width - m_data[OffsetX] && m_data[Height] <= height - m_data[OffsetY];
			}

			/**
			 * @brief Reduces the sizes of the rectangle.
			 * @param area A reference to an area.
			 * @return bool
			 */
			bool
			cropOnOverflow (const Rectangle< data_t > & area) noexcept
			{
				auto change = false;

				if ( m_data[OffsetX] < area.m_data[OffsetX] )
				{
					m_data[OffsetX] = area.m_data[OffsetX];

					change = true;
				}

				if ( m_data[Width] > area.m_data[Width] )
				{
					m_data[Width] = area.m_data[Width];

					change = true;
				}

				if ( m_data[OffsetY] < area.m_data[OffsetY] )
				{
					m_data[OffsetY] = area.m_data[OffsetY];

					change = true;
				}

				if ( m_data[Height] > area.m_data[Height] )
				{
					m_data[Height] = area.m_data[Height];

					change = true;
				}

				return change;
			}

			/**
			 * @brief Reduces the sizes of the rectangle.
			 * @param width The final width.
			 * @param height The final height.
			 * @return bool
			 */
			bool
			cropOnOverflow (data_t width, data_t height) noexcept
			{
				auto change = false;

				if ( m_data[OffsetX] > width )
				{
					m_data[OffsetX] = 0;

					change = true;
				}

				if ( m_data[OffsetY] > height )
				{
					m_data[OffsetY] = 0;

					change = true;
				}

				if ( m_data[Width] > width - m_data[OffsetX] )
				{
					m_data[Width] = width - m_data[OffsetX];

					change = true;
				}

				if ( m_data[Height] > height - m_data[OffsetY] )
				{
					m_data[Height] = height - m_data[OffsetY];

					change = true;
				}

				return change;
			}

			/**
			 * @brief Returns the aspect ratio.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			aspectRatio () const noexcept
			{
				if ( m_data[Height] == 0 )
				{
					return 1;
				}

				return m_data[Width] / m_data[Height];
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Rectangle & obj) noexcept
			{
				out <<
					"Rectangle data :" "\n"
					"Position : X " << obj.m_data[0] << ", Y " << obj.m_data[1] << "\n"
					"Position B : X " << obj.offsetXb() << ", Y " << obj.offsetYb() << "\n"
					"Size : " << obj.m_data[2] << " X " << obj.m_data[3] << '\n';

				return out;
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Rectangle & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			std::array< data_t, 4 > m_data{0, 0, 1, 1};
	};
}
