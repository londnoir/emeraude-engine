/*
 * Emeraude/Graphics/RenderableInstance/VertexBufferBinding.hpp
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
#include <cstddef>
#include <string>
#include <sstream>
#include <iostream>

/* Local inclusions for inheritances. */
#include "FlagTrait.hpp"

/* Local inclusions for usages. */
#include "Graphics/Types.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief Vertex buffer binding flags.
	 */
	enum VertexBufferBindingFlagBits
	{
		PerInstance = 1,
		RequestPrimitiveRestart = 2,
		IsPositionAbsolute = 4,
		IsDynamicVertexBuffer = 8
	};

	/**
	 * @brief Describes the data inside a vertex attribute binding. How many elements and the primitive used.
	 * @extends Libraries::FlagTrait
	 */
	class VertexBufferBinding final : public Libraries::FlagTrait< uint32_t >
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VertexBufferBinding"};

			/**
			 * @brief Constructs a VBO binding format to describes how to use it.
			 * @param binding The binding index.
			 * @param elementCount The element count to make a vertex.
			 * @param topology The type of primitive.
			 * @param bufferFlags The buffer flags.
			 */
			VertexBufferBinding (uint32_t binding, size_t elementCount, Topology topology, uint32_t bufferFlags) noexcept;

			/**
			 * @brief Equality operator.
			 * @param operand A reference to an other VertexBufferBinding.
			 * @return bool
			 */
			[[nodiscard]]
			bool operator== (const VertexBufferBinding & operand) const noexcept;

			/**
			 * @brief Different operator.
			 * @param operand A reference to an other VertexBufferBinding.
			 * @return bool
			 */
			[[nodiscard]]
			bool operator!= (const VertexBufferBinding & operand) const noexcept;

			/**
			 * @brief Returns the element count to make a vertex.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t elementCount () const noexcept;

			/**
			 * @brief Returns the vertex size in bytes at a specific binding point.
			 * @note Same as VertexBufferFormat::elementCount() * sizeof(float).
			 * @param size_t
			 */
			[[nodiscard]]
			size_t size () const noexcept;

			/**
			 * @brief Returns the type of primitive.
			 * @return Topology
			 */
			[[nodiscard]]
			Topology topology () const noexcept;

			/**
			 * @brief Returns whether the binding is per instance or per vertex.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			perInstance () const noexcept
			{
				return this->isFlagEnabled(PerInstance);
			}

			/**
			 * @brief Returns whether the binding request to active primitive restart.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			requestPrimitiveRestart () const noexcept
			{
				return this->isFlagEnabled(RequestPrimitiveRestart);
			}

			/**
			 * @brief Returns whether the position in vertex attributes are expressed in absolute coordinates.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			isPositionAbsolute () const noexcept
			{
				return this->isFlagEnabled(IsPositionAbsolute);
			}

			/**
			 * @brief Returns whether the VBO is dynamic.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			isDynamicVertexBuffer () const noexcept
			{
				return this->isFlagEnabled(IsDynamicVertexBuffer);
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const VertexBufferBinding & obj);

			/**
			 * @brief Stringify the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const VertexBufferBinding & obj) noexcept;

		private:

			uint32_t m_binding;
			size_t m_elementCount;
			Topology m_topology;
	};
}
