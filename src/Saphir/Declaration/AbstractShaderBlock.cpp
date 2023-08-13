/*
 * Emeraude/Saphir/Declaration/AbstractShaderBlock.cpp
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

#include "AbstractShaderBlock.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Saphir::Declaration
{
	using namespace Libraries;

	const char * ShaderBlockTracerTag = "ShaderBlock";

	AbstractShaderBlock::AbstractShaderBlock (Key name, uint32_t location, Key instanceName, size_t arraySize) noexcept
		: BlockInterface(name, instanceName, arraySize), m_location(location)
	{

	}

	bool
	AbstractShaderBlock::isValid () const noexcept
	{
		if ( this->name() == nullptr )
			return false;

		if ( this->instanceName().empty() )
			return false;

		if ( m_members.empty() )
			return false;

		return true;
	}

	size_t
	AbstractShaderBlock::bytes () const noexcept
	{
		return 0;
	}

	uint32_t
	AbstractShaderBlock::location () const noexcept
	{
		return m_location;
	}

	const std::vector< std::pair< Key, Member::ShaderBlock > > &
	AbstractShaderBlock::members () const noexcept
	{
		return m_members;
	}

	bool
	AbstractShaderBlock::addMember (VariableType type, Key name, Key interpolation) noexcept
	{
		if ( Utility::contains(m_members, name) )
		{
			TraceError{ShaderBlockTracerTag} << "This shader block has already a member named '" << name << "' !";

			return false;
		}

		m_members.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(type, name, interpolation, 0)
		);

		return true;
	}

	bool
	AbstractShaderBlock::addMember (const Structure & structure, Key interpolation) noexcept
	{
		const auto name = structure.instanceName().c_str();

		if ( Utility::contains(m_members, name) )
		{
			TraceError{ShaderBlockTracerTag} << "This shader block has already a member named '" << name << "' !";

			return false;
		}

		if ( !this->addStructure(structure.name(), structure) )
			return false;

		m_members.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(VariableType::Structure, name, interpolation, 0)
		);

		return true;
	}

	bool
	AbstractShaderBlock::addArrayMember (VariableType type, Key name, size_t arraySize, Key interpolation) noexcept
	{
		if ( Utility::contains(m_members, name) )
		{
			TraceError{ShaderBlockTracerTag} << "This shader block has already a member named '" << name << "' !";

			return false;
		}

		if ( arraySize == 0 )
			return false;

		m_members.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(type, name, interpolation, arraySize)
		);

		return true;
	}

	bool
	AbstractShaderBlock::addArrayMember (const Structure & structure, size_t arraySize, Key interpolation) noexcept
	{
		const auto name = structure.instanceName().c_str();

		if ( Utility::contains(m_members, name) )
		{
			TraceError{ShaderBlockTracerTag} << "This shader block has already a member named '" << name << "' !";

			return false;
		}

		if ( arraySize == 0 )
			return false;

		if ( !this->addStructure(structure.name(), structure) )
			return false;

		m_members.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(VariableType::Structure, name, interpolation, arraySize)
		);

		return true;
	}
}
