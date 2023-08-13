/*
 * Libraries/KVParser/Parser.hpp
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
#include <map>
#include <string>

/* Local inclusions */
#include "Section.hpp"

namespace Libraries::KVParser
{
	class Parser final
	{
		public:

			using Sections = std::map< std::string, Section >;

			Parser () noexcept = default;

			[[nodiscard]]
			Sections & sections () noexcept;

			[[nodiscard]]
			const Sections & sections () const noexcept;

			[[nodiscard]]
			Section & section (const std::string & label) noexcept;

			bool read (const std::string & filepath) noexcept;

			bool write (const std::string & filepath) noexcept;

		private:

			enum class LineType
			{
				None = 0,
				Headers = 1,
				Comment = 2,
				SectionTitle = 3,
				Definition = 4
			};

			static std::string parseSectionTitle (const std::string & line) noexcept;

			static LineType getLineType (const std::string & line) noexcept;

			Sections m_sections{};
			Sections::iterator m_currentSection{};
	};
}
