/*
 * Emeraude/Saphir/Declaration/AbstractBufferBackedBlock.cpp
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

#include "AbstractBufferBackedBlock.hpp"

/* C/C++ standard libraries. */
#include <sstream>

/* Local inclusions. */
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Saphir::Declaration
{
	using namespace Libraries;
	using namespace Keys;

	constexpr auto TracerTag{"BufferBackedBlock"};

	AbstractBufferBackedBlock::AbstractBufferBackedBlock (uint32_t set, uint32_t binding, MemoryLayout memoryLayout, Key name, Key instanceName, size_t arraySize) noexcept
		: BlockInterface(name, instanceName, arraySize), m_set(set), m_binding(binding), m_memoryLayout(memoryLayout)
	{

	}

	bool
	AbstractBufferBackedBlock::isValid () const noexcept
	{
		if ( this->name() == nullptr )
		{
			return false;
		}

		if ( this->instanceName().empty() )
		{
			return false;
		}

		if ( m_members.empty() )
		{
			return false;
		}

		return true;
	}

	void
	AbstractBufferBackedBlock::setMatrixStorageOrder (MatrixStorageOrder matrixStorageOrder) noexcept
	{
		m_matrixStorageOrder = matrixStorageOrder;
	}

	size_t
	AbstractBufferBackedBlock::bytes () const noexcept
	{
		size_t size = 0;

		for ( const auto & structure : this->structures() )
		{
			size += structure.second.bytes();
		}

		for ( const auto & member : this->members() )
		{
			size += member.second.bytes();
		}

		/* FIXME: Check alignment. */
		if ( this->arraySize() > 1UL )
		{
			size *= this->arraySize();
		}

		return size;
	}

	uint32_t
	AbstractBufferBackedBlock::set () const noexcept
	{
		return m_set;
	}

	uint32_t
	AbstractBufferBackedBlock::binding () const noexcept
	{
		return m_binding;
	}

	MatrixStorageOrder
	AbstractBufferBackedBlock::matrixStorageOrder () const noexcept
	{
		return m_matrixStorageOrder;
	}

	const std::vector< std::pair< Key, Member::BufferBackedBlock > > &
	AbstractBufferBackedBlock::members () const noexcept
	{
		return m_members;
	}

	bool
	AbstractBufferBackedBlock::addMember (VariableType type, Key name, Key layout) noexcept
	{
		if ( Utility::contains(m_members, name) )
		{
			TraceError{TracerTag} << "This buffer backed block has already a member named '" << name << "' !";

			return false;
		}

		m_members.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(type, name, layout, 0)
		);

		return true;
	}

	bool
	AbstractBufferBackedBlock::addMember (const Structure & structure, Key layout) noexcept
	{
		const auto * name = structure.instanceName().c_str();

		if ( Utility::contains(m_members, name) )
		{
			TraceError{TracerTag} << "This buffer backed block has already a member named '" << name << "' !";

			return false;
		}

		if ( !this->addStructure(structure.name(), structure) )
		{
			return false;
		}

		m_members.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(VariableType::Structure, name, layout, 0)
		);

		return true;
	}

	bool
	AbstractBufferBackedBlock::addArrayMember (VariableType type, Key name, size_t arraySize, Key layout) noexcept
	{
		if ( Utility::contains(m_members, name) )
		{
			TraceError{TracerTag} << "This buffer backed block has already a member named '" << name << "' !";

			return false;
		}

		if ( arraySize == 0UL )
		{
			return false;
		}

		m_members.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(type, name, layout, arraySize)
		);

		return true;
	}

	bool
	AbstractBufferBackedBlock::addArrayMember (const Structure & structure, size_t arraySize, Key layout) noexcept
	{
		const auto * name = structure.instanceName().c_str();

		if ( Utility::contains(m_members, name) )
		{
			TraceError{TracerTag} << "This buffer backed block has already a member named '" << name << "' !";

			return false;
		}

		if ( arraySize == 0 )
		{
			return false;
		}

		if ( !this->addStructure(structure.name(), structure) )
		{
			return false;
		}

		m_members.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(VariableType::Structure, name, layout, arraySize)
		);

		return true;
	}

	std::string
	AbstractBufferBackedBlock::getLayoutQualifier () const noexcept
	{
		std::stringstream code{};

		code << GLSL::Layout << " (";

		switch ( m_matrixStorageOrder )
		{
			case MatrixStorageOrder::Default :
				/* Nothing ... */
				break;

			case MatrixStorageOrder::ColumnMajor :
				code << GLSL::ColumnMajor;
				break;

			case MatrixStorageOrder::RowMajor :
				code << GLSL::RowMajor;
				break;
		}

		switch ( m_memoryLayout )
		{
			case MemoryLayout::Shared :
				code << GLSL::Shared << ", ";
				break;

			case MemoryLayout::Packed :
				code << GLSL::Packed << ", ";
				break;

			case MemoryLayout::Std140 :
				code << GLSL::Std140 << ", ";
				break;

			case MemoryLayout::Std430 :
				code << GLSL::Std430 << ", ";
				break;
		}

		code << GLSL::Set << " = " << m_set << ", " << GLSL::Binding << " = " << m_binding << ") ";

		return code.str();
	}
}
