/*
 * Emeraude/Graphics/RenderableInstance/VertexBufferFormat.cpp
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

#include "VertexBufferFormat.hpp"

/* C/C++ standard libraries */
#include <algorithm>

/* Local inclusions. */
#include "Graphics/Types.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	using namespace Libraries;

	bool
	VertexBufferFormat::operator== (const VertexBufferFormat & operand) const noexcept
	{
		if ( this == &operand )
			return true;

		if ( m_bindings.size() == operand.m_bindings.size() )
		{
			const auto limit = m_bindings.size();

			for ( size_t index = 0; index < limit; index++ )
			{
				if ( m_bindings[index].binding != operand.m_bindings[index].binding )
					return false;

				if ( m_bindings[index].stride != operand.m_bindings[index].stride )
					return false;

				if ( m_bindings[index].inputRate != operand.m_bindings[index].inputRate )
					return false;
			}
		}
		else
		{
			return false;
		}

		if ( m_attributes.size() == operand.m_attributes.size() )
		{
			const auto limit = m_attributes.size();

			for ( size_t index = 0; index < limit; index++ )
			{
				if ( m_attributes[index].location != operand.m_attributes[index].location )
					return false;

				if ( m_attributes[index].binding != operand.m_attributes[index].binding )
					return false;

				if ( m_attributes[index].format != operand.m_attributes[index].format )
					return false;

				if ( m_attributes[index].offset != operand.m_attributes[index].offset )
					return false;
			}
		}
		else
		{
			return false;
		}

		if ( m_bindingFormats != operand.m_bindingFormats )
			return false;

		return true;
	}

	bool
	VertexBufferFormat::operator!= (const VertexBufferFormat & operand) const noexcept
	{
		return !this->operator==(operand);
	}

	const VertexBufferBinding *
	VertexBufferFormat::binding (uint32_t binding) const noexcept
	{
		const auto it = m_bindingFormats.find(binding);

		return it != m_bindingFormats.cend() ? &(it->second) : nullptr;
	}

	const std::map< uint32_t, VertexBufferBinding > &
	VertexBufferFormat::vertexAttributes () const noexcept
	{
		return m_bindingFormats;
	}

	const std::vector< VkVertexInputBindingDescription > &
	VertexBufferFormat::bindings () const noexcept
	{
		return m_bindings;
	}

	const std::vector< VkVertexInputAttributeDescription > &
	VertexBufferFormat::attributes () const noexcept
	{
		return m_attributes;
	}

	void
	VertexBufferFormat::setInputAttribute (uint32_t location, uint32_t binding, VkFormat format, uint32_t offset) noexcept
	{
		m_attributes.emplace_back(VkVertexInputAttributeDescription{
			.location = location,
			.binding = binding,
			.format = format,
			.offset = offset
		});
	}

	void
	VertexBufferFormat::setBinding (uint32_t binding, uint32_t stride, VkVertexInputRate inputRate) noexcept
	{
		m_bindings.emplace_back(VkVertexInputBindingDescription{
			.binding = binding,
			.stride = stride,
			.inputRate = inputRate
		});
	}

	void
	VertexBufferFormat::saveBindingData (uint32_t binding, size_t elementCount, Topology topology, uint32_t bufferFlags) noexcept
	{
		m_bindingFormats.emplace(binding, VertexBufferBinding{
			binding,
			elementCount,
			topology,
			bufferFlags
		});
	}

	bool
	VertexBufferFormat::isPresent (VertexAttributeType attribute) const noexcept
	{
		const auto location = static_cast< uint32_t >(attribute);

		return std::any_of(m_attributes.cbegin(), m_attributes.cend(), [location] (const auto & item) {
			return item.location == location;
		});
	}

	std::ostream &
	operator<< (std::ostream & out, const VertexBufferFormat & obj)
	{
		out << "Vertex buffer format @" << &obj << "\n";

		if ( obj.m_bindingFormats.empty() )
		{
			out << " - Binding formats : None !" "\n";
		}
		else
		{
			out << " - Binding formats :" "\n";

			for ( const auto & bindingFormat : obj.m_bindingFormats )
			{
				out << "\t" << "Binding index:" << bindingFormat.first << " (" << bindingFormat.second << ")\n";
			}
		}

		if ( obj.m_bindings.empty() )
		{
			out << " - Binding descriptions : None !" "\n";
		}
		else
		{
			out << " - Binding descriptions :" "\n";

			for ( const auto & binding : obj.m_bindings )
			{
				out << "\t" <<
					"Binding point:" << binding.binding << ", "
					"stride:" << binding.stride << ", "
					"input rate: " << binding.inputRate << "\n";
			}
		}

		if ( obj.m_attributes.empty() )
		{
			out << " - Attribute descriptions : None !" "\n";
		}
		else
		{
			out << " - Attribute descriptions :" "\n";

			for ( const auto & attribute : obj.m_attributes )
			{
				out << "\t" <<
					"Attribute location:" << attribute.location << " (" << to_cstring(static_cast< VertexAttributeType >(attribute.location)) << "), "
					"binding:" << attribute.binding << ", "
					"format:" << attribute.format << ", "
					"offset:" << attribute.offset << "\n";
			}
		}

		return out << "\n";
	}

	std::string
	to_string (const VertexBufferFormat & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
