/*
 * Libraries/SourceCodeParser.cpp
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

#include "SourceCodeParser.hpp"

/* C/C++ standard libraries. */
#include <iomanip>
#include <sstream>

/* Local inclusions */
#include "String.hpp"

namespace Libraries
{
	SourceCodeParser::SourceCodeParser (const std::string & sourceCode) noexcept
		: m_lines(String::explode(sourceCode, '\n'))
	{

	}

	void
	SourceCodeParser::notice (size_t line, size_t column, const std::string & notice) noexcept
	{
		if ( line < 1 )
		{
			this->notice(notice);
		}
		else
		{
			m_notices.emplace(line, std::multimap<size_t, std::string>{}).first->second.emplace(column, notice);
		}
	}

	void
	SourceCodeParser::notice (const std::string & notice) noexcept
	{
		m_endNotices.emplace_back(notice);
	}

	std::string
	SourceCodeParser::getParsedSourceCode (int numberWidth) const noexcept
	{
		std::stringstream outputSource{};

		for ( auto lineIt = m_lines.cbegin(); lineIt != m_lines.cend(); ++lineIt )
		{
			const auto lineNumber = std::distance(m_lines.cbegin(), lineIt) + 1;

			/* Print the line of code. */
			outputSource << std::setfill(' ') << std::setw(numberWidth) << lineNumber << "| " << *lineIt << '\n';

			/* Print possible notices under the line. */
			auto noticeIt = m_notices.find(lineNumber);

			if ( noticeIt != m_notices.cend() )
			{
				for ( const auto & item : noticeIt->second )
				{
					outputSource << std::string(numberWidth + 2 + item.first, '~') << "^ " << item.second << '\n';
				}

				outputSource << '\n';
			}
		}

		/* Print possible end notices. */
		if ( !m_endNotices.empty() )
		{
			outputSource << '\n';

			for ( const auto & endNotice : m_endNotices )
			{
				outputSource << endNotice << '\n';
			}
		}

		return outputSource.str();
	}
}
