/*
 * src/Libraries/KVParser/Parser.cpp
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

#include "Parser.hpp"

/* STL inclusions. */
#include <fstream>
#include <iostream>

/* Local inclusions. */
#include "Libraries/String.hpp"

namespace Libraries::KVParser
{
	std::string
	Parser::parseSectionTitle (const std::string & line) noexcept
	{
		auto start = line.find_first_of('[');
		auto length = line.find_last_of(']');

		if ( start != std::string::npos && length != std::string::npos )
		{
			return {line, start + 1, length - 1};
		}

		return {};
	}

	Parser::LineType
	Parser::getLineType (const std::string & line) noexcept
	{
		for ( auto character : line )
		{
			switch ( character )
			{
				case '@' :
					return LineType::Headers;

				case '[' :
					return LineType::SectionTitle;

				case '#' :
					return LineType::Comment;

				case '=' :
					return LineType::Definition;

				default :
					/* We don't care about this char ... */
					break;
			}
		}

		return LineType::None;
	}

	Parser::Sections &
	Parser::sections () noexcept
	{
		return m_sections;
	}

	const Parser::Sections &
	Parser::sections () const noexcept
	{
		return m_sections;
	}

	Section &
	Parser::section (const std::string & label) noexcept
	{
		const auto sectionIt = m_sections.find(label);

		if ( sectionIt != m_sections.cend() )
		{
			return sectionIt->second;
		}

		return m_sections[label] = Section();
	}

	bool
	Parser::read (const std::string & filepath) noexcept
	{
		std::ifstream file{filepath};

		if ( file.is_open() )
		{
			std::string line{};

			/* This is the default section. */
			auto * currentSection = &this->section("main");

			/* Count the sections. */
			while ( std::getline(file, line) )
			{
				switch ( Parser::getLineType(line) )
				{
					case LineType::SectionTitle :
					{
						auto sectionName = Parser::parseSectionTitle(line);

						if ( !sectionName.empty() )
						{
							currentSection = &this->section(sectionName);
						}
					}
						break;

					case LineType::Definition :
					{
						auto equalSignPosition = line.find_first_of('=');

						if ( equalSignPosition != std::string::npos )
						{
							auto key = String::trim(line.substr(0, equalSignPosition));
							auto value = String::trim(line.substr(equalSignPosition + 1));

							currentSection->addVariable(key, Variable{value});
						}
					}
						break;

					case LineType::None :
					case LineType::Headers :
					case LineType::Comment :
						break;
				}
			}

			file.close();

			/* Indicates the parser state. */
			return true;
		}

		return false;
	}

	bool
	Parser::write (const std::string & filepath) noexcept
	{
		std::ofstream file{filepath, std::ios::out | std::ios::trunc};

		if ( file.is_open() )
		{
			for ( const auto & section : m_sections )
			{
				file << "[" << section.first << "]" "\n";

				section.second.write(file);

				file << "\n";
			}

			file.close();

			return true;
		}

		return false;
	}
}
