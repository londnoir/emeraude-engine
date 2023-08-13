/*
 * Libraries/PixelFactory/Area.hpp
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

/* C/C++ standard libraries */
#include <array>
#include <iostream>
#include <sstream>
#include <string>

/* Local inclusions */
#include "Math/Vector.hpp"
#include "Utility.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief Defines an area inside a pixmap to work with finite pixels.
	 * @tparam data_t The unsigned integer precision. Default size_t.
	 */
	template< typename data_t = size_t, std::enable_if_t< std::is_integral_v< data_t >, bool > = false, std::enable_if_t< std::is_unsigned_v< data_t >, bool > = false >
	class Area final
	{
		public:

			/**
			 * @brief Constructs a default area.
			 */
			Area () noexcept = default;

			/**
			 * @brief Constructs an area by providing only dimension.
			 * @param width The width of the area.
			 * @param height The height of the area.
			 */
			constexpr Area (data_t width, data_t height) noexcept
				: m_data{0, 0, width, height}
			{

			}

			/**
			 * @brief Constructs an area by providing position and dimension.
			 * @param offsetX The position of the area in X.
			 * @param offsetY The position of the area in Y.
			 * @param width The width of the area.
			 * @param height The height of the area.
			 */
			constexpr Area (data_t offsetX, data_t offsetY, data_t width, data_t height) noexcept
				: m_data{offsetX, offsetY, width, height}
			{

			}

			/**
			 * @brief Checks surface of Area.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator> (const Area & operand) const noexcept
			{
				return ( (m_data[Width] * m_data[Height]) > (operand.m_data[Width] * operand.m_data[Height]) );
			}

			/**
			 * @brief operator >= overload.
			 * @param operand A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator>= (const Area & operand) const noexcept
			{
				return ( (m_data[Width] * m_data[Height]) >= (operand.m_data[Width] * operand.m_data[Height]) );
			}

			/**
			 * @brief operator < overload.
			 * @param operand A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator< (const Area & operand) const noexcept
			{
				return ( (m_data[Width] * m_data[Height]) < (operand.m_data[Width] * operand.m_data[Height]) );
			}

			/**
			 * @brief operator <= overload.
			 * @param operand A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator<= (const Area & operand) const noexcept
			{
				return ( (m_data[Width] * m_data[Height]) <= (operand.m_data[Width] * operand.m_data[Height]) );
			}

			/**
			 * @brief operator + overload.
			 * @param operand A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			Area &
			operator+ (const Area & rhs)
			{
				return Area::merge(*this, rhs);
			}

			/**
			 * @brief operator += overload.
			 * @param operand A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			Area &
			operator+= (const Area & rhs)
			{
				*this = Area::merge(*this, rhs);

				return *this;
			}

			/**
			 * @brief Sets the offset X of the area.
			 * @param xOffset The new offset.
			 * @return void
			 */
			void
			setOffsetX (data_t xOffset) noexcept
			{
				m_data[OffsetX] = xOffset;
			}

			/**
			 * @brief Sets the offset Y of the area.
			 * @param yOffset The new offset.
			 * @return void
			 */
			void
			setOffsetY (data_t yOffset) noexcept
			{
				m_data[OffsetY] = yOffset;
			}

			/**
			 * @brief Sets the offsets of the area.
			 * @param xOffset The new X offset.
			 * @param yOffset The new Y offset.
			 * @return void
			 */
			void
			setOffsets (data_t xOffset, data_t yOffset) noexcept
			{
				m_data[OffsetX] = xOffset;
				m_data[OffsetY] = yOffset;
			}

			/**
			 * @brief Sets the offsets of the area.
			 * @param vectorOffset A reference to a vector.
			 * @return void
			 */
			void
			setOffsets (const Math::Vector< 2, data_t > & vectorOffset) noexcept
			{
				m_data[OffsetX] = vectorOffset.x();
				m_data[OffsetY] = vectorOffset.y();
			}

			/**
			 * @brief Sets the width of the area.
			 * @param width The new width.
			 * @return void
			 */
			void
			setWidth (data_t width) noexcept
			{
				m_data[Width] = width;
			}

			/**
			 * @brief Sets the height of the area.
			 * @param height The new height.
			 * @return void
			 */
			void
			setHeight (data_t height) noexcept
			{
				m_data[Height] = height;
			}

			/**
			 * @brief Sets the size of the area.
			 * @param width The new width.
			 * @param height The new height.
			 * @return void
			 */
			void
			setSize (data_t width, data_t height) noexcept
			{
				m_data[Width] = width;
				m_data[Height] = height;
			}

			/**
			 * @brief Sets the size of the area.
			 * @param sizeVector A reference to a vector.
			 * @return void
			 */
			void
			setSize (const Math::Vector< 2, data_t > & sizeVector) noexcept
			{
				m_data[Width] = sizeVector.x();
				m_data[Height] = sizeVector.y();
			}

			/**
			 * @brief Moves the offset X of the area.
			 * @param xMove The value to add on X offset.
			 * @return void
			 */
			void
			moveX (data_t xMove) noexcept
			{
				m_data[OffsetX] += xMove;
			}

			/**
			 * @brief Moves the offset Y of the area.
			 * @param yMove The value to add on Y offset.
			 * @return void
			 */
			void
			moveY (data_t yMove) noexcept
			{
				m_data[OffsetY] += yMove;
			}

			/**
			 * @brief Moves the offset of the area.
			 * @param xMove The value to add on X offset.
			 * @param yValue The value to add on Y offset.
			 * @return void
			 */
			void
			move (data_t xMove, data_t yMove) noexcept
			{
				m_data[OffsetX] += xMove;
				m_data[OffsetY] += yMove;
			}

			/**
			 * @brief Moves the offset of the area.
			 * @param vectorMove A reference to a vector.
			 * @return void
			 */
			void
			move (const Math::Vector< 2, data_t > & vectorMove) noexcept
			{
				m_data[OffsetX] += vectorMove.x();
				m_data[OffsetY] += vectorMove.y();
			}

			/**
			 * @brief Modifies the width of the area by adding a value.
			 * @param value The value to add to the current width.
			 * @return void
			 */
			void
			modifyWidthBy (data_t value) noexcept
			{
				m_data[Width] += value;
			}

			/**
			 * @brief Modifies the height of the area by adding a value.
			 * @param value The value to add to the current height.
			 * @return void
			 */
			void
			modifyHeightBy (data_t value) noexcept
			{
				m_data[Height] += value;
			}

			/**
			 * @brief Modifies the size of the area by adding values.
			 * @param widthValue The value to add to the current width.
			 * @param heightValue The value to add to the current height.
			 * @return void
			 */
			void
			modifyWidthBy (data_t widthValue, data_t heightValue) noexcept
			{
				m_data[Width] += widthValue;
				m_data[Height] += heightValue;
			}

			/**
			 * @brief Modifies the size of the area by adding values.
			 * @param vectorSize A reference to a vector.
			 * @return void
			 */
			void
			modifyWidthBy (const Math::Vector< 2, data_t > & vectorSize) noexcept
			{
				m_data[Width] += vectorSize.x();
				m_data[Height] += vectorSize.y();
			}

			/**
			 * @brief Reset the area to null.
			 * @return void
			 */
			void
			reset () noexcept
			{
				for ( auto & element : m_data )
				{
					element = 0;
				}
			}

			/**
			 * @brief Returns the X offset of the area.
			 * @param data_t
			 */
			[[nodiscard]]
			data_t
			offsetX () const noexcept
			{
				return m_data[OffsetX];
			}

			/**
			 * @brief Returns the Xb offset of the area.
			 * @note Same as Area::offsetX() + Area::width() - 1.
			 * @param data_t
			 */
			[[nodiscard]]
			data_t
			offsetXb () const noexcept
			{
				return this->offsetX() + this->width() - 1;
			}

			/**
			 * @brief Returns the Y offset of the area.
			 * @param data_t
			 */
			[[nodiscard]]
			data_t
			offsetY () const noexcept
			{
				return m_data[OffsetY];
			}

			/**
			 * @brief Returns the Yb offset of the area.
			 * @note Same as Area::offsetY() + Area::height() - 1.
			 * @param data_t
			 */
			[[nodiscard]]
			data_t
			offsetYb () const noexcept
			{
				return this->offsetY() + this->height() - 1;
			}

			/**
			 * @brief Returns the width of the area.
			 * @param data_t
			 */
			[[nodiscard]]
			data_t
			width () const noexcept
			{
				return m_data[Width];
			}

			/**
			 * @brief Returns the height of the area.
			 * @param data_t
			 */
			[[nodiscard]]
			data_t
			height () const noexcept
			{
				return m_data[Height];
			}

			/**
			 * @brief Returns the coordinates of the bottom-left of the area.
			 * @tparam output_t The data type for the vector.
			 * @return Vector< 2, output_t >
			 */
			template< typename output_t, std::enable_if_t< std::is_arithmetic_v< output_t >, bool > = false >
			[[nodiscard]]
			Math::Vector< 2, output_t >
			bottomLeft () const noexcept
			{
				return {static_cast< output_t >(this->offsetX()), static_cast< output_t >(this->offsetY())};
			}

			/**
			 * @brief Returns the coordinates of the bottom-right of the area.
			 * @tparam output_t The data type for the vector.
			 * @return Vector< 2, output_t >
			 */
			template< typename output_t, std::enable_if_t< std::is_arithmetic_v< output_t >, bool > = false >
			[[nodiscard]]
			Math::Vector< 2, output_t >
			bottomRight () const noexcept
			{
				return {static_cast< output_t >(this->offsetXb()), static_cast< output_t >(this->offsetY())};
			}

			/**
			 * @brief Returns the coordinates of the top-left of the area.
			 * @tparam output_t The data type for the vector.
			 * @return Vector< 2, output_t >
			 */
			template< typename output_t, std::enable_if_t< std::is_arithmetic_v< output_t >, bool > = false >
			[[nodiscard]]
			Math::Vector< 2, output_t >
			topLeft () const noexcept
			{
				return {static_cast< output_t >(this->offsetX()), static_cast< output_t >(this->offsetYb())};
			}

			/**
			 * @brief Returns the coordinates of the top-right of the area.
			 * @tparam output_t The data type for the vector.
			 * @return Vector< 2, output_t >
			 */
			template< typename output_t, std::enable_if_t< std::is_arithmetic_v< output_t >, bool > = false >
			[[nodiscard]]
			Math::Vector< 2, output_t >
			topRight () const noexcept
			{
				return {static_cast< output_t >(this->offsetXb()), static_cast< output_t >(this->offsetYb())};
			}

			/**
			 * @brief Checks if the area is not null.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				if ( m_data[Width] == 0 )
				{
					return false;
				}

				if ( m_data[Height] == 0 )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Checks if the area intersect these parameters.
			 * @param width A width to test the area against.
			 * @param height A width to test the area against.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isIntersect (data_t width, data_t height) const noexcept
			{
				if ( m_data[OffsetX] >= width )
				{
					return false;
				}

				if ( m_data[OffsetY] >= height )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Checks if the whole area lie inside these parameters.
			 * @param width A width to test the area against.
			 * @param height A width to test the area against.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isInside (data_t width, data_t height) const noexcept
			{
				/* NOTE: Check if the X axis segment is not bigger than the target width. */
				if ( (m_data[OffsetX] + m_data[Width]) >= width )
				{
					return false;
				}

				/* NOTE: Same on Y axis. */
				if ( (m_data[OffsetY] + m_data[Height]) >= height )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Checks if the whole area is outside these parameters.
			 * @param width A width to test the area against.
			 * @param height A width to test the area against.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isOutside (data_t width, data_t height) const noexcept
			{
				if ( m_data[OffsetX] >= width )
				{
					return true;
				}

				if ( m_data[OffsetY] >= height )
				{
					return true;
				}

				return false;
			}

			/**
			 * @brief Crops the size area to fit the parameters.
			 * @param width A width to test the area against.
			 * @param height A width to test the area against.
			 * @return bool
			 */
			bool
			cropOnOverflow (data_t width, data_t height) noexcept
			{
				auto changes = false;

				/* NOTE: Check if the X axis segment is not bigger than the target width. */
				if ( (m_data[OffsetX] + m_data[Width]) >= width )
				{
					m_data[Width] = m_data[OffsetX] + m_data[Width] - width;

					changes = true;
				}

				/* NOTE: Same on Y axis. */
				if ( (m_data[OffsetY] + m_data[Height]) >= height )
				{
					m_data[Height] = m_data[OffsetY] + m_data[Height] - height;

					changes = true;
				}

				return changes;
			}

			/**
			 * @brief Returns the aspect ratio of the area.
			 * @return float
			 */
			[[nodiscard]]
			float
			aspectRatio () const noexcept
			{
				if ( !this->isValid() )
				{
					return 0.0F;
				}

				return static_cast< float >(m_data[Width]) / static_cast< float >(m_data[Height]);
			}

			/**
			 * @brief Expands the area by merging an other one.
			 * @param area A reference to an other area.
			 * @return void
			 */
			[[deprecated("Use the static method instead !")]]
			void
			merge (const Area & area) noexcept
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
			 * @brief Merges two area.
			 * @param areaA A reference to an area.
			 * @param areaB A reference to an area.
			 * @return void
			 */
			static
			Area
			merge (const Area & areaA, const Area & areaB) noexcept
			{
				if ( &areaA == &areaB )
				{
					return areaA;
				}

				/* Checking area validity. */
				if ( areaA.isValid() )
				{
					if ( !areaB.isValid() )
					{
						return areaA;
					}
				}
				else if ( areaB.isValid() )
				{
					return areaB;
				}
				else
				{
					/* No one is valid ! */
					return {};
				}

				Area area{};

				/* Operations in X. */
				if ( areaA.m_data[OffsetX] < areaB.m_data[OffsetX] )
				{
					if ( (areaA.m_data[OffsetX] + areaA.m_data[Width]) < (areaB.m_data[OffsetX] + areaB.m_data[Width]) )
					{
						area.setWidth((areaB.m_data[OffsetX] + areaB.m_data[Width]) - areaA.m_data[OffsetX]);
					}
					else
					{
						area.setWidth(areaA.m_data[Width]);
					}

					area.setOffsetX(areaA.m_data[OffsetX]);
				}
				else
				{
					if ( (areaA.m_data[OffsetX] + areaA.m_data[Width]) > (areaB.m_data[OffsetX] + areaB.m_data[Width]) )
					{
						area.setWidth((areaA.m_data[OffsetX] + areaA.m_data[Width]) - areaB.m_data[OffsetX]);
					}
					else
					{
						area.setWidth(areaB.m_data[Width]);
					}

					area.setOffsetX(areaB.m_data[OffsetX]);
				}

				/* Operations in Y. */
				if ( areaA.m_data[OffsetY] < areaB.m_data[OffsetY] )
				{
					if ( (areaA.m_data[OffsetY] + areaA.m_data[Height]) < (areaB.m_data[OffsetY] + areaB.m_data[Height]) )
					{
						area.setHeight((areaB.m_data[OffsetY] + areaB.m_data[Height]) - areaA.m_data[OffsetY]);
					}
					else
					{
						area.setHeight(areaA.m_data[Height]);
					}

					area.setOffsetY(areaA.m_data[OffsetY]);
				}
				else
				{
					if ( (areaA.m_data[OffsetY] + areaA.m_data[Height]) > (areaB.m_data[OffsetY] + areaB.m_data[Height]) )
					{
						area.setHeight((areaA.m_data[OffsetY] + areaA.m_data[Height]) - areaB.m_data[OffsetY]);
					}
					else
					{
						area.setHeight(areaB.m_data[Height]);
					}

					area.setOffsetY(areaB.m_data[OffsetY]);
				}

				return area;
			}

			/**
			 * @brief Reduces the area by subtracting an other one.
			 * @todo Make a class operand overload to do this.
			 * @param area A reference to an other area.
			 * @return bool
			 */
			[[deprecated("Should be replace by a static method")]]
			bool
			intersect (const Area & area) noexcept
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
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream &
			operator<< (std::ostream & out, const Area & obj)
			{
				return out << "Area data ;\n"
					"X : " << obj.m_data[0] << " -> " << obj.offsetXb() << "\n"
					"Y : " << obj.m_data[1] << " -> " << obj.offsetYb() << "\n"
					"Width : " << obj.m_data[2] << "\n"
					"Height : " << obj.m_data[3] << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string
			to_string (const Area & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			static constexpr auto OffsetX = 0UL;
			static constexpr auto OffsetY = 1UL;
			static constexpr auto Width = 2UL;
			static constexpr auto Height = 3UL;

			std::array< data_t, 4 > m_data{0, 0, 0, 0};
	};
}
