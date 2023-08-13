/*
 * Libraries/VertexFactory/ShapeVertex.hpp
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
#include <type_traits>

namespace Libraries::VertexFactory
{
	/**
	 * @brief The shape vertex class.
	 * @tparam data_t The precision type of vertex data. Default float.
	 */
	template< typename data_t, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	class ShapeVertex final
	{
		public:

			/**
			 * @brief Constructs a default vertex.
			 */
			ShapeVertex () noexcept = default;

			/**
			 * @brief Constructs a vertex from attributes.
			 * @param position A reference to a vector for the position in space.
			 * @param normal A reference to a vector for the normal. Default Z+.
			 * @param textureCoordinates A reference to a vector for texture coordinates. Default [0, 0].
			 */
			explicit
			ShapeVertex (const Math::Vector< 3, data_t > & position, const Math::Vector< 3, data_t > & normal = Math::Vector< 3, data_t >::positiveZ(), const Math::Vector< 2, data_t > & textureCoordinates = {}) noexcept
				: m_position(position), m_normal(normal), m_textureCoordinates(textureCoordinates)
			{

			}

			/**
			 * @brief Sets the vertex position.
			 * @param position A reference to a vector for the position in space.
			 */
			void
			setPosition (const Math::Vector< 3, data_t > & position) noexcept
			{
				m_position = position;
			}

			/**
			 * @brief Sets the vertex position.
			 * @param position A reference to a vector for the position in space.
			 */
			void
			setPosition (const Math::Vector< 4, data_t > & position) noexcept
			{
				m_position[Math::X] = position[Math::X];
				m_position[Math::Y] = position[Math::Y];
				m_position[Math::Z] = position[Math::Z];
			}

			/**
			 * @brief Sets the vertex tangent.
			 * @param tangent A reference to a 3D vector for the tangent.
			 */
			void
			setTangent (const Math::Vector< 3, data_t > & tangent) noexcept
			{
				m_tangent = tangent;
			}

			/**
			 * @brief Sets the vertex tangent.
			 * @param tangent A reference to a 4D vector for the tangent.
			 */
			void
			setTangent (const Math::Vector< 4, data_t > & tangent) noexcept
			{
				m_tangent[Math::X] = tangent[Math::X];
				m_tangent[Math::Y] = tangent[Math::Y];
				m_tangent[Math::Z] = tangent[Math::Z];
			}

			/**
			 * @brief Sets the vertex normal.
			 * @param tangent A reference to a 3D vector for the normal.
			 */
			void
			setNormal (const Math::Vector< 3, data_t > & normal) noexcept
			{
				m_normal = normal;
			}

			/**
			 * @brief Sets the vertex normal.
			 * @param tangent A reference to a 4D vector for the normal.
			 */
			void
			setNormal (const Math::Vector< 4, data_t > & normal) noexcept
			{
				m_normal[Math::X] = normal[Math::X];
				m_normal[Math::Y] = normal[Math::Y];
				m_normal[Math::Z] = normal[Math::Z];
			}

			/**
			 * @brief Sets the vertex texture coordinates.
			 * @param textureCoordinates A reference to a 2D vector for the coordinates.
			 */
			void
			setTextureCoordinates (const Math::Vector< 2, data_t > & textureCoordinates) noexcept
			{
				m_textureCoordinates = textureCoordinates;
			}

			/**
			 * @brief Sets the vertex texture coordinates.
			 * @param textureCoordinates A reference to a 3D vector for the coordinates.
			 */
			void
			setTextureCoordinates (const Math::Vector< 3, data_t > & textureCoordinates) noexcept
			{
				m_textureCoordinates[Math::X] = textureCoordinates[Math::X];
				m_textureCoordinates[Math::Y] = textureCoordinates[Math::Y];
			}

			/**
			 * @brief Sets the vertex texture coordinates.
			 * @param textureCoordinates A reference to a 4D vector for the coordinates.
			 */
			void
			setTextureCoordinates (const Math::Vector< 4, data_t > & textureCoordinates) noexcept
			{
				m_textureCoordinates[Math::X] = textureCoordinates[Math::X];
				m_textureCoordinates[Math::Y] = textureCoordinates[Math::Y];
			}

			/**
			 * @brief Returns the vertex position vector.
			 * @return const Math::Vector< 3, data_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 3, data_t > &
			position () const noexcept
			{
				return m_position;
			}

			/**
			 * @brief Returns the vertex tangent vector.
			 * @return const Math::Vector< 3, data_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 3, data_t > &
			tangent () const noexcept
			{
				return m_tangent;
			}

			/**
			 * @brief Returns the vertex normal vector.
			 * @return const Math::Vector< 3, data_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 3, data_t > &
			normal () const noexcept
			{
				return m_normal;
			}

			/**
			 * @brief Returns the vertex binormal vector.
			 * @return const Math::Vector< 3, data_t > &
			 */
			[[nodiscard]]
			inline
			Math::Vector< 3, data_t >
			binormal () const noexcept
			{
				return Math::Vector< 3, data_t >::crossProduct(m_normal, m_tangent);
			}

			/**
			 * @brief Returns the vertex texture coordinates vector.
			 * @return const Math::Vector< 2, data_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 2, data_t > &
			textureCoordinates () const noexcept
			{
				return m_textureCoordinates;
			}

			/**
			 * @brief Flips the Y-Axis of attributes.
			 */
			void
			flipYAxis () noexcept
			{
				m_position[Math::Y] = -m_position[Math::Y];
				m_tangent[Math::Y] = -m_tangent[Math::Y];
				m_normal[Math::Y] = -m_normal[Math::Y];
				//m_textureCoordinates[Math::Y] = -m_textureCoordinates[Math::Y];
			}

		private:

			Math::Vector< 3, data_t > m_position{};
			Math::Vector< 3, data_t > m_tangent{1, 0, 0};
			Math::Vector< 3, data_t > m_normal{0, 0, 1};
			Math::Vector< 2, data_t > m_textureCoordinates{0, 0};
	};
}
