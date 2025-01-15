/*
 * src/Saphir/Code.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Code.hpp"

namespace Emeraude::Saphir
{
	Code::Code (CodeGeneratorInterface & generator, Location type, size_t depth) noexcept
		: m_generator(generator), m_type(type), m_indent(depth, '\t')
	{
		m_code << m_indent;
	}

	Code::~Code ()
	{
		m_code << '\n';

		switch ( m_type )
		{
			case Location::Top:
				m_generator.addTopInstruction(m_code.str());
				break;

			case Location::Main:
				m_generator.addInstruction(m_code.str());
				break;

			case Location::Output:
				m_generator.addOutputInstruction(m_code.str());
				break;
		}
	}

	Code &
	Code::operator<< (const Line & value) noexcept
	{
		switch ( value )
		{
			/* NOTE: End of the line char + new indent. */
			case Line::End :
				m_code << '\n' << m_indent;
				break;

			/* NOTE: Double end of the line chars + new indent. */
			case Line::Blank :
				m_code << "\n\n" << m_indent;
				break;
		}

		return *this;
	}
}
