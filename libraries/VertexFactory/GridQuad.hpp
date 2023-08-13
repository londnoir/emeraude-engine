/*
 * Libraries/VertexFactory/GridQuad.hpp
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
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

namespace Libraries::VertexFactory
{
	// NOLINTBEGIN(readability-identifier-length, *-magic-numbers)

	/**
	 * @brief Describe a grid cell.
	 * @note A cell is a square.
	 */
	class GridQuad final
	{
		public:

			/**
			 * @brief Constructs a default grid quad.
			 */
			GridQuad () noexcept = default;

			/**
			 * @brief Constructs a grid quad.
			 * @param topLeftIndex
			 * @param bottomLeftIndex
			 * @param topRightIndex
			 * @param bottomRightIndex
			 */
			GridQuad (size_t topLeftIndex, size_t bottomLeftIndex, size_t topRightIndex, size_t bottomRightIndex) noexcept
				: m_topLeftIndex(topLeftIndex), m_bottomLeftIndex(bottomLeftIndex), m_topRightIndex(topRightIndex), m_bottomRightIndex(bottomRightIndex)
			{

			}

			/**
			 * @brief Returns whether the quad is valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				return m_topLeftIndex != 0 || m_bottomLeftIndex != 0 || m_topRightIndex != 0 || m_bottomRightIndex != 0;
			}

			/**
			 * @brief Sets the quad top left to vertex index.
			 * @param index The vertex index from the geometry data.
			 * @return void
			 */
			void
			setTopLeftIndex (size_t index) noexcept
			{
				m_topLeftIndex = index;
			}

			/**
			 * @brief Sets the quad bottom left to vertex index.
			 * @param index The vertex index from the geometry data.
			 * @return void
			 */
			void
			setBottomLeftIndex (size_t index) noexcept
			{
				m_bottomLeftIndex = index;
			}

			/**
			 * @brief Sets the quad top right to vertex index.
			 * @param index The vertex index from the geometry data.
			 * @return void
			 */
			void
			setTopRightIndex (size_t index) noexcept
			{
				m_topRightIndex = index;
			}

			/**
			 * @brief Sets the quad bottom right to vertex index.
			 * @param index The vertex index from the geometry data.
			 * @return void
			 */
			void
			setBottomRightIndex (size_t index) noexcept
			{
				m_bottomRightIndex = index;
			}

			/**
			 * @brief Returns the quad top left index to the geometry data.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			topLeftIndex () const noexcept
			{
				return m_topLeftIndex;
			}

			/**
			 * @brief Returns the quad bottom left index to the geometry data.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			bottomLeftIndex () const noexcept
			{
				return m_bottomLeftIndex;
			}

			/**
			 * @brief Returns the quad top right index to the geometry data.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			topRightIndex () const noexcept
			{
				return m_topRightIndex;
			}

			/**
			 * @brief Returns the quad bottom right index to the geometry data.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			bottomRightIndex () const noexcept
			{
				return m_bottomRightIndex;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const GridQuad & obj) noexcept
			{
				return out << "Grid quad data :\n"
					"Top-left index : " << obj.m_topLeftIndex << "\n"
					"Bottom-left index : " << obj.m_bottomLeftIndex << "\n"
					"Top-Right index : " << obj.m_topRightIndex << "\n"
					"Bottom-Right index : " << obj.m_bottomRightIndex << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const GridQuad & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			size_t m_topLeftIndex{0};
			size_t m_bottomLeftIndex{0};
			size_t m_topRightIndex{0};
			size_t m_bottomRightIndex{0};
	};

	// NOLINTEND(readability-identifier-length, *-magic-numbers)
}
