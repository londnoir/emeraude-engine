/*
 * Emeraude/Graphics/RenderableInstance/VertexBufferFormat.hpp
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
#include <string>
#include <vector>
#include <map>

/* Local inclusions for usages. */
#include "Saphir/ShaderGenerator.hpp"
#include "VertexBufferBinding.hpp"

/* Third-party libraries. */
#include "Third-Party-Inclusion/vulkan.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	/**
	 * @brief Declares the data format of a vertex buffer object (VBO).
	 */
	class VertexBufferFormat final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VertexBufferFormat"};

			/**
			 * @brief Constructs a vertex buffer format.
			 */
			VertexBufferFormat () noexcept = default;

			/**
			 * @brief Equality operator.
			 * @param operand A reference to an other VertexBufferFormat.
			 * @return bool
			 */
			[[nodiscard]]
			bool operator== (const VertexBufferFormat & operand) const noexcept;

			/**
			 * @brief Different operator.
			 * @param operand A reference to an other VertexBufferFormat.
			 * @return bool
			 */
			[[nodiscard]]
			bool operator!= (const VertexBufferFormat & operand) const noexcept;

			/**
			 * @brief Returns the binding structure.
			 * @param binding The binding point.
			 * @return const VertexBufferBinding *
			 */
			[[nodiscard]]
			const VertexBufferBinding * binding (uint32_t binding) const noexcept;

			/**
			 * @brief Returns vertex attributes.
			 * @return const std::map< uint32_t, VertexBufferBinding > &
			 */
			[[nodiscard]]
			const std::map< uint32_t, VertexBufferBinding > & vertexAttributes () const noexcept;

			/**
			 * @brief Returns vertex input binding descriptions.
			 * @return const std::vector< VkVertexInputBindingDescription > &
			 */
			[[nodiscard]]
			const std::vector< VkVertexInputBindingDescription > & bindings () const noexcept;

			/**
			 * @brief Returns vertex input attribute descriptions.
			 * @return const std::vector< VkVertexInputAttributeDescription > &
			 */
			[[nodiscard]]
			const std::vector< VkVertexInputAttributeDescription > & attributes () const noexcept;

			/**
			 * @brief Sets an attribute to the vertex buffer format.
			 * @param location The location of the attribute.
			 * @param binding The binding point.
			 * @param format The attribute format.
			 * @param offset The offset inside the vertex buffer object.
			 * @return void
			 */
			void setInputAttribute (uint32_t location, uint32_t binding, VkFormat format, uint32_t offset) noexcept;

			/**
			 * @brief Sets a binding.
			 * @param binding The binding point.
			 * @param stride The stride inside the vertex buffer object.
			 * @param inputRate The type of passing vertex.
			 * @return void
			 */
			void setBinding (uint32_t binding, uint32_t stride, VkVertexInputRate inputRate) noexcept;

			/**
			 * @brief Saves the binding informations.
			 * @param binding The binding point.
			 * @param elementCount The element count.
			 * @param topology The geometry topology.
			 * @param bufferFlags The vertex buffer object flags.
			 */
			void saveBindingData (uint32_t binding, size_t elementCount, Topology topology, uint32_t bufferFlags) noexcept;

			/**
			 * @brief Returns wheter a vertex attribute is present in the format.
			 * @param attribute The vertex attribute type.
			 * @return bool
			 */
			[[nodiscard]]
			bool isPresent (VertexAttributeType attribute) const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const VertexBufferFormat & obj);

			/**
			 * @brief Stringify the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const VertexBufferFormat & obj) noexcept;

		private:

			std::vector< VkVertexInputBindingDescription > m_bindings{};
			std::vector< VkVertexInputAttributeDescription > m_attributes{};
			std::map< uint32_t, VertexBufferBinding > m_bindingFormats{};
	};
}
