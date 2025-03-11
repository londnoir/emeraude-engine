/*
 * src/Libs/KVParser/Parser.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <map>
#include <string>

/* Local inclusions. */
#include "Section.hpp"

namespace EmEn::Libs::KVParser
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
