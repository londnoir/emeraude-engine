/*
 * Emeraude/Saphir/CodeGeneratorInterface.cpp
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

#include "CodeGeneratorInterface.hpp"

/* C/C++ standard libraries. */
#include <sstream>

namespace Emeraude::Saphir
{
	void
	CodeGeneratorInterface::addTopInstruction (const std::string & code) noexcept
	{
		m_topInstructions.emplace_back(code);
	}

	void
	CodeGeneratorInterface::addInstruction (const std::string & code) noexcept
	{
		m_instructions.emplace_back(code);
	}

	void
	CodeGeneratorInterface::addOutputInstruction (const std::string & code) noexcept
	{
		m_outputInstructions.emplace_back(code);
	}

	void
	CodeGeneratorInterface::addComment (const std::string & comment, size_t depth) noexcept
	{
		m_instructions.emplace_back((std::stringstream{} << std::string(depth, '\t') << "/* " << comment << " */\n").str());
	}

	std::string
	CodeGeneratorInterface::getCode (const std::string & prependTopInstructions, const std::string & prependOutputInstructions) const noexcept
	{
		std::stringstream code{};

		if ( !prependTopInstructions.empty() || !m_topInstructions.empty() )
		{
			code <<
				"\t" "/* Preparation instructions */" "\n" <<

				prependTopInstructions;

			for (  const auto & line : m_topInstructions )
			{
				code << line;
			}

			code << '\n';
		}

		if ( !m_instructions.empty() )
		{
			code << "\t" "/* Main instructions */" "\n";

			for (  const auto & line : m_instructions )
			{
				code << line;
			}

			code << '\n';
		}

		if ( !prependOutputInstructions.empty() || !m_outputInstructions.empty() )
		{
			code <<
				"\t" "/* Output instructions */" "\n" <<

				prependOutputInstructions;

			for (  const auto & line : m_outputInstructions )
			{
				code << line;
			}
		}

		return code.str();
	}
}
